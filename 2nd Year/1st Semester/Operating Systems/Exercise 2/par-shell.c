/*
Grupo 11
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "list.h"
#include <pthread.h>
#include <time.h>
#include "commandlinereader.h"

#define EXIT_COMMAND "exit"
#define MAXARGS 7 /* Comando + 5 argumentos opcionais + espaco para NULL */
#define STATUS_INFO_LINE_SIZE 50
#define BUFFER_SIZE 100

int numchildren = 0;
int exit_flag = 0; /*Flag que ordena a saida da tarefa monitora*/

static list_t *list; /*Lista que guarda a informacao dos processos*/

pthread_t thread; /*Tarefa*/
pthread_mutex_t mutex; /*Trinco logico*/

void *monitor(){	/*Tarefa monitora*/
	while(1){
		pthread_mutex_lock(&mutex);
		if(numchildren>0){
			int status, childpid;
			pthread_mutex_unlock(&mutex);
			
			childpid = wait(&status);
			pthread_mutex_lock(&mutex);
			if (childpid < 0) {
	  			
	  			if (errno == EINTR) {
	  				pthread_mutex_unlock(&mutex);
	  				continue;
	 			}
	  			else {
	    			perror("Error waiting for child.\n");
	    			pthread_mutex_unlock(&mutex);
	    			exit (EXIT_FAILURE);
	  			}
			}
			update_terminated_process(list, childpid, status, time(NULL));
			numchildren--;
			pthread_mutex_unlock(&mutex);
		}
		else if(exit_flag == 1 && numchildren == 0){
			pthread_mutex_unlock(&mutex);
			break;
		}
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
	pthread_exit(NULL);
}

int main (int argc, char** argv) {
	
	char *args[MAXARGS];
	char buffer[BUFFER_SIZE];

	list = lst_new();

	pthread_mutex_init(&mutex, NULL);

  	if(pthread_create(&thread, NULL, *monitor ,NULL) != 0){
  		printf("Erro na criacao da tarefa\n");
  		exit(EXIT_FAILURE);
  	}

  	printf("Insert your commands:\n");

	while (1) {
    	int numargs, pid;
    	time_t starttime;

    	numargs = readLineArguments(args, MAXARGS, buffer, BUFFER_SIZE);
    
    	if (numargs < 0){
    		printf("Erro no readLineArguments\n");
    		continue;
    	}

		else if (numargs == 0)
    		continue;

   		if(strcmp(args[0], EXIT_COMMAND) == 0) { 
    		pthread_mutex_lock(&mutex);
			exit_flag = 1;
			pthread_mutex_unlock(&mutex);

      		pthread_join(thread, NULL);
      		lst_print(list);
      		pthread_mutex_destroy(&mutex);
      		lst_destroy(list);
	      	exit(EXIT_SUCCESS);
    	}
   		
  		pid = fork();	/*Cria processo*/
  		starttime = time(NULL);
  		if (pid < 0) {
			perror("Failed to create new process.");
			exit(EXIT_FAILURE);
  		}
  
  		if (pid > 0) { 	  /* Codigo do processo pai */
			pthread_mutex_lock(&mutex);
			insert_new_process(list, pid, starttime);
			numchildren ++;
			pthread_mutex_unlock(&mutex);
  		}
  		
  		else { /* Codigo do processo filho */
			if (execv(args[0], args) < 0) {
  				perror("Could not run child program. Child will exit.");
  				exit(EXIT_FAILURE);
			}
  		}
  	} 
}