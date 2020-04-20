/*Grupo 11*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#include "commandlinereader.h"
#include "list.h"


#define EXIT_COMMAND "exit"

#define MAXARGS        7
#define BUFFER_SIZE  100
#define LINE_SIZE 100

#define MAXPAR 4


int num_children = 0, num_max = MAXPAR, num_exec = 0; /*num_max: Contador para processos maximos | num_exec: Contador de processos em execucao*/
int flag_exit = 0; /* do not exit */
int totalTime = 0, totalIteration = -1;/*Variaveis relacionadas com o ficheiro log.txt: Numero total de iteracoes e tempo total no ficheiro*/

list_t *proc_data;

FILE *text; /*Ficheiro*/

pthread_mutex_t data_ctrl;

pthread_cond_t condLaunch; 
pthread_cond_t condCatch;


/* 
+-----------------------------------------------------------------------*/
void cond_wait_launch(void){
  if(pthread_cond_wait(&condLaunch, &data_ctrl) != 0){
    perror("Error in pthread_cond_wait()\n");
    exit(EXIT_FAILURE);
  }
}

/* 
+-----------------------------------------------------------------------*/
void cond_signal_Launch(void) {
  if(pthread_cond_signal(&condLaunch) != 0){
    perror("Error in pthread_cond_signalt()\n");
    exit(EXIT_FAILURE);
  }
}

/* 
+-----------------------------------------------------------------------*/
void cond_wait_Catch(void) {
  if(pthread_cond_wait(&condCatch, &data_ctrl) != 0){
    perror("Error in pthread_cond_wait()\n");
    exit(EXIT_FAILURE);
  }
}

/* 
+-----------------------------------------------------------------------*/
void cond_signal_Catch(void) {
  if(pthread_cond_signal(&condCatch) != 0){
    perror("Error in pthread_cond_signal()\n");
    exit(EXIT_FAILURE);
  }
}

/* 
+-----------------------------------------------------------------------*/
void mutex_lock(void) {
  if(pthread_mutex_lock(&data_ctrl) != 0){
    fprintf(stderr, "Error in pthread_mutex_lock()\n");
    exit(EXIT_FAILURE);
  }
}


/* 
+-----------------------------------------------------------------------*/
void mutex_unlock(void) {
  if(pthread_mutex_unlock(&data_ctrl) != 0)
  {
    fprintf(stderr, "Error in pthread_mutex_unlock()\n");
    exit(EXIT_FAILURE);
  }
}

/* 
+-----------------------------------------------------------------------*/
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
	fclose(text); /*Fecha o ficheiro*/
  pthread_exit(NULL); /*Termina a thread monitora*/
}


/* 
+-----------------------------------------------------------------------*/

int main (int argc, char** argv) {
    pthread_t tid;
    char buffer[BUFFER_SIZE];
    int numargs;
    char *args[MAXARGS];
    time_t start_time;
    int pid;
    char line[LINE_SIZE]; /*Cadeia de caracteres correspondente a cada linha do ficheiro*/


    /* criar estrutura de dados de monitorização */
    proc_data = lst_new();

    /*Abre o ficheiro log.txt, se nao existir cria um novo*/
    text = fopen("log.txt", "a+");

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
    
    /* criar condicao de variavel*/
    if(pthread_cond_init(&condLaunch, NULL) != 0){
      fprintf(stderr, "Error creating condition.\n");
      exit(EXIT_FAILURE);
    }

    if(pthread_cond_init(&condCatch, NULL) != 0){
      fprintf(stderr, "Error creating condition.\n");
      exit(EXIT_FAILURE);
    }

    /* criar thread */
    if (pthread_create(&tid, NULL, tarefa_monitora, NULL) != 0) {
      fprintf(stderr, "Error creating thread.\n");
      exit(EXIT_FAILURE);
    }

    while(1) {
      printf("Insert your command: ");
      numargs = readLineArguments(args, MAXARGS, buffer, BUFFER_SIZE);

      if (numargs < 0) {
        printf("Error in readLineArguments()\n");
        continue;
      }
      if (numargs == 0) /* empty line; read another one */
        continue;

      if (strcmp(args[0], EXIT_COMMAND) == 0) {
        printf("Ending...\n");
        break;
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
      else if (pid == 0) {  /* child */
        if (execv(args[0], args) == -1) {
  	       perror("Could not run child program. Child will exit.");
  	       exit(EXIT_FAILURE);
        }
      }
    }

    /* received command exit */

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
    return 0; /* ok */
}



