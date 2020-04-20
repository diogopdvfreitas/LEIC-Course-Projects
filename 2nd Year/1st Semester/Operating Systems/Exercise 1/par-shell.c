#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define DIM 7		//Constante de tamanho 7 para definir o tamanho máximo do comando

int n_child=0;
char* arg[DIM];

/*Estrutura*/

typedef struct process *linkprocess;	//Ponteiro do tipo process

struct process{ 						//Estrutura do processo
	int pidd;
	int sts;
};

void printProcess() {
	/*funcao responsavel por guardar a informacao dos pids e status na estrutura. Posteriormente emprime a estrutura toda */
	int i, pidTerminou, estado;
	linkprocess vet_process[n_child];
	for(i=0;i<n_child;i++){
		pidTerminou = wait(&estado);
		vet_process[i] = (linkprocess)malloc(sizeof(struct process));
		vet_process[i]->pidd = pidTerminou;
		vet_process[i]->sts = estado;
	}
	for(i=0;i<n_child;i++){
		if(WIFEXITED(vet_process[i]->sts))
		  printf("Pid: %d, Status: %d\n", vet_process[i]->pidd, WEXITSTATUS(vet_process[i]->sts));
		else
		  printf("Processo %d saiu sem chamar exit", vet_process[i]->pidd);
		free(vet_process[i]);
	}
}

int main() {
	/* funcao main: le o input da shell. v[0] -> comando(nome do ficheiro). Os outros elementos do vetor sao argumentos.*/
	int pid;
	readLineArguments(arg, 6);
	while(strcmp(arg[0],"exit")){
		pid = fork();
		if(pid == -1) { /*Se o pid for negativo, significa que houve erro na criacao do processo*/
			perror("Erro no fork");
		}
		if(pid == 0){
			execv(arg[0], arg);
			exit(EXIT_FAILURE);
			}
		else{
			n_child++;
		}
		readLineArguments(arg, 6);
	}
	printProcess();
	exit(EXIT_SUCCESS);
}