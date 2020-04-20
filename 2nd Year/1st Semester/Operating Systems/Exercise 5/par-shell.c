/*Grupo 11*/
/*include de bibliotecas*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>


/*include ficheiros adicionais*/
#include "commandlinereader.h"
#include "list.h"
#include "listterminal.h"


/*defenição de Macros*/
/*Criacao de constantes*/
#define MAXPAR          4
#define MAXARGS         7
#define BUFF_SIZE       100
#define LINE_SIZE       100
#define FILENAME_SIZE   40
#define PATHNAME        "/tmp/par-shell-in"
#define STAT_COMMAND    "stats"
#define EXIT_COMMAND    "exit"
#define NEW_TERMINAL    "<new>"
#define EXIT_GLOBAL     "exit-global"



/*inicializacao de variaveis globais*/
pthread_t tid;
int num_children = 0, num_max = MAXPAR, num_exec = 0; /*num_max: Contador para processos maximos | num_exec: Contador de processos em execucao*/
int flag_exit = 0; /* do not exit */
int totalTime = 0, totalIteration = -1;/*Variaveis relacionadas com o ficheiro log.txt: Numero total de iteracoes e tempo total no ficheiro*/
int par_shell_in; /*Pipe para leitura*/
int par_shell_process; /*Pipe para escrita*/
char filename[FILENAME_SIZE]; /*nome do ficheiro para guardar o stdout dos processos*/
char *pathname = PATHNAME;  /*Pathname onde se encontra o par-shell-in*/

list_t *proc_data;    /*Lista com a informação dos processo filhos*/
terminal_t *terminal_data;    /*Lista com informação dos terminais*/


FILE *text; /*Ficheiro*/
FILE *out_pid; /*Ficheiro que guarda o stdout*/


/*mutex*/
pthread_mutex_t data_ctrl;


/*variaveis de condicao*/
pthread_cond_t condLaunch; 
pthread_cond_t condCatch;



/*-----------------------------------------------*/
/*-------CRIACAO DE FUNCOES AUXILIARES-----------*/
/*-----------------------------------------------*/
void exit_parshell();
void fopenLog(){
  if((text = fopen("log.txt", "a+")) == NULL){
    perror("Error in fopen()\n");
    exit(EXIT_FAILURE);
  }
}

void fcloseLog(){
  if(fclose(text) == EOF){
    perror("Error in fclose()\n");
    exit(EXIT_FAILURE);
  }
}

void sighandlerkill(int signum){
  kill_terminal(terminal_data);
  exit_parshell();

}


void cond_wait_launch(void){
  if(pthread_cond_wait(&condLaunch, &data_ctrl) != 0){
    perror("Error in pthread_cond_wait()\n");
    exit(EXIT_FAILURE);
  }
}


void cond_signal_Launch(void) {
  if(pthread_cond_signal(&condLaunch) != 0){
    perror("Error in pthread_cond_signalt()\n");
    exit(EXIT_FAILURE);
  }
}


void cond_wait_Catch(void) {
  if(pthread_cond_wait(&condCatch, &data_ctrl) != 0){
    perror("Error in pthread_cond_wait()\n");
    exit(EXIT_FAILURE);
  }
}


void cond_signal_Catch(void) {
  if(pthread_cond_signal(&condCatch) != 0){
    perror("Error in pthread_cond_signal()\n");
    exit(EXIT_FAILURE);
  }
}


void mutex_lock(void) {
  if(pthread_mutex_lock(&data_ctrl) != 0){
    fprintf(stderr, "Error in pthread_mutex_lock()\n");
    exit(EXIT_FAILURE);
  }
}


void mutex_unlock(void) {
  if(pthread_mutex_unlock(&data_ctrl) != 0){
    fprintf(stderr, "Error in pthread_mutex_unlock()\n");
    exit(EXIT_FAILURE);
  }
}



/*-----------------------------------------------*/
/*---------------TAREFA MONITORA-----------------*/
/*-----------------------------------------------*/

void *tarefa_monitora(void *arg_ptr) {
  int status, childpid, processTime; /*processTime guarda o tempo de execusao do processo*/
  time_t end_time;
  
  
  printf(" *** Tarefa monitora activa.\n");

  while(1) {
	  mutex_lock();
	  while(num_exec == 0){
		  cond_wait_Catch();
	  }
	  num_exec--;
	  if(num_children == 0) {
			if(flag_exit == 1) {
		    mutex_unlock();
		    printf(" *** Tarefa monitora terminou.\n");
        break;
		  }
    }
	  mutex_unlock();
	  
	  /* wait for a child process */
	  childpid = wait(&status);
	  if (childpid == -1) {
	    perror("Error waiting for child");
	    exit(EXIT_FAILURE);
	  }
	  
	  end_time = time(NULL);

	  mutex_lock();
	  num_children --;
	  num_max++;

    /*Coloca no ficheiro log.txt as novas 3 linhas*/
	  processTime = update_terminated_process(proc_data, childpid, end_time, status);/*funcao alterada para returnar o tempo de execucao do processo*/
	  totalTime+= processTime;
	  fprintf(text, "%s %d\n%s %d %s %d %s\n%s %d %s\n","iteracao",++totalIteration, "pid:", childpid, "execution time:", processTime ,"s", "total execution time:", totalTime, "s");
  	fflush(text);
    cond_signal_Launch();
	  mutex_unlock();

  }
	fcloseLog(); /*Fecha o ficheiro*/
  pthread_exit(NULL); /*Termina a thread monitora*/
}



/*-----------------------------------------------*/
/*-----------------FUNCAO MAIN-------------------*/
/*-----------------------------------------------*/

int main (int argc, char** argv) {
  int n;
  time_t start_time;
  int pid;
  char* args[MAXARGS];
  char line[LINE_SIZE]; /*Cadeia de caracteres correspondente a cada linha do ficheiro*/
  char buff[100];
  char message[100];

  proc_data = lst_new(); /* criar estrutura de dados de monitorização */
  
  terminal_data = terminal_new(); /*Cria biblioteca de pids correspondentes aos terminais*/

  fopenLog();  /*Abre o ficheiro log.txt, se nao existir cria um novo*/

  if(signal(SIGINT, sighandlerkill) == SIG_ERR){
    fprintf(stderr, "Error in signal\n");
    exit(EXIT_FAILURE);
  }

  /*Atualiza as variaveis do numero total de iteracoes e o tempo total ate ao momento*/
  while(fgets(line, LINE_SIZE, text) != NULL){
    if(sscanf(line, "iteracao %d", &totalIteration) == 1){
      continue;
    }
    if(sscanf(line, "total execution time: %d", &totalTime) == 1){
    }
  }

  /* criar mutex */
  if(pthread_mutex_init(&data_ctrl, NULL) != 0) {
    fprintf(stderr, "Error creating mutex.\n");
    exit(EXIT_FAILURE);
  }
  
  /* criar variavel de condicao*/
  if(pthread_cond_init(&condLaunch, NULL) != 0){
    fprintf(stderr, "Error creating condition.\n");
    exit(EXIT_FAILURE);
  }

  /* criar variavel de condicao*/
  if(pthread_cond_init(&condCatch, NULL) != 0){
    fprintf(stderr, "Error creating condition.\n");
    exit(EXIT_FAILURE);
  }

  /* criar thread */
  if (pthread_create(&tid, NULL, tarefa_monitora, NULL) != 0) {
    fprintf(stderr, "Error creating thread.\n");
    exit(EXIT_FAILURE);
  }

  if(unlink(pathname) < 0){
    if(errno != ENOENT)
      fprintf(stderr, "Error unliking pipe\n");
  }

  if(mkfifo(pathname, 0777) < 0){
	  fprintf(stderr, "Error in mkfifo.\n");
	  exit(EXIT_FAILURE);
  }


  if((par_shell_in = open(pathname, O_RDONLY)) < 0){
	  fprintf(stderr, "Error opening pipe Lê.\n");
	  exit(EXIT_FAILURE);
  }
  
  if(dup(STDIN_FILENO) == -1){
    perror("Error in dup()\n");
    exit(EXIT_FAILURE);
  }
  if(close(STDIN_FILENO) == -1){
    perror("Error in close()\n");
    exit(EXIT_FAILURE);
  }
  if(dup(par_shell_in) == -1){
    perror("Error in dup()\n");
    exit(EXIT_FAILURE);
  }

  while(1) {
    n = readLineArguments(args, MAXARGS, buff, BUFF_SIZE);
    if(n == 0)
		  continue;
    else if(n < 0){
      fprintf(stderr, "Error in readLineArguments()\n");
      exit(EXIT_FAILURE);
    }


  	if(strcmp(args[0], EXIT_COMMAND) == 0){
        pid = atoi(args[1]);
        if(unlink(args[2]) < 0){
          if(errno != ENOENT)
              fprintf(stderr, "Error unliking pipe\n");
        }
        remove_terminal(terminal_data, pid);
       	continue;  
    }  
    if(strcmp(args[0], NEW_TERMINAL) == 0){
      pid = atoi(args[1]);
      
      insert_new_terminal(terminal_data, pid);
      continue;
    }
    if(strcmp(args[0], EXIT_GLOBAL) == 0){
      kill_terminal(terminal_data);
      exit_parshell();
    }

  	if (strcmp(args[0], STAT_COMMAND) == 0) {
  		sprintf(message, "Numero de processos atuais: %d\nTempo de processos executados: %d",num_children, totalTime);
      if((par_shell_process = open(args[1], O_WRONLY)) < 0){
        fprintf(stderr, "Error opening pipe1.\n");
        exit(EXIT_FAILURE);
      }
      if((write(par_shell_process, message, strlen(message))) < 0){
  	    fprintf(stderr, "Error writing pipe.\n");
  	    exit(EXIT_FAILURE);
      }
      if(close(par_shell_process) == -1){
        perror("Error in close()\n");
        exit(EXIT_FAILURE);
      }
      continue;
    }


    /* process a command */
    mutex_lock();
  	while(num_max == 0){
  	cond_wait_launch();
  	}
  	num_max--;
  	mutex_unlock();
   

   	pid = fork();
  	start_time = time(NULL);
  	if (pid == -1) {
    	perror("Failed to create new process.");
    	exit(EXIT_FAILURE);
  	}

  	if (pid > 0) {  /* parent */
      mutex_lock();
      num_children++;
      num_exec++;
      insert_new_process(proc_data, pid, start_time);
      cond_signal_Catch();
      mutex_unlock(); 
  	}
  	else if (pid == 0) { /* child */
      sprintf(filename, "par-shell-out-%d.txt", getpid());
      if((out_pid = fopen(filename, "a+")) == NULL){
        perror("Error in fopen()\n");
        exit(EXIT_FAILURE);
      }
      if(close(STDOUT_FILENO) == -1){
        perror("Error in close()\n");
        exit(EXIT_FAILURE);
      }
      if((dup(fileno(out_pid))) == -1){
        perror("Error in dup()\n");
        exit(EXIT_FAILURE);
      }
      signal(SIGINT,SIG_IGN);
      if (execv(args[0], args) == -1) {
        perror("Could not run child program. Child will exit.");
      	exit(EXIT_FAILURE);
      }
      fclose(out_pid);
    }
  }
  return 0;
}

void exit_parshell(){
  /* received command exit */
  if(close(par_shell_in) == -1){
    perror("Error in close()\n");
    exit(EXIT_FAILURE);
  }
  if(unlink(pathname) < 0){
    if(errno != ENOENT)
      fprintf(stderr, "Error unliking pipe\n");
  }

  /* request the monitoring thread to end */
  mutex_lock();
  flag_exit = 1;
  num_exec++;
  cond_signal_Catch();
  mutex_unlock();
  
  /* wait for thread to end */
  if(pthread_join(tid, NULL) != 0) {
    fprintf(stderr, "Error joining thread.\n");
    exit(EXIT_FAILURE);
  }
  
  /*Print da lista de processos*/
  lst_print(proc_data);

  /* clean up and exit */
  pthread_mutex_destroy(&data_ctrl);
  if(pthread_cond_destroy(&condCatch) != 0){
    perror("Error in pthread_cond_destroy()\n");
    exit(EXIT_FAILURE);
  }
  if(pthread_cond_destroy(&condLaunch) != 0){
    perror("Error in pthread_cond_destroy()\n");
    exit(EXIT_FAILURE);
  }
  lst_destroy(proc_data);
  terminal_destroy(terminal_data);
  
  exit(EXIT_SUCCESS);
}



