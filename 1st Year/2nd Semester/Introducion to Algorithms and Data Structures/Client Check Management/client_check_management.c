/*Introdução a Algoritmos e Estruturas de Dados, Projecto 1*/

/*
Diogo Freitas   81586 
Nuno Cartier    81718
Pedro Caldeira  81888
*/

/*---------------Bibliotecas, Constantes, Estruturas e Variáveis----------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "avl.h"

#define COMMANDLEN	12

int nch, vch;

/*--------------------------------Protótipos------------------------------------*/

void addchequetoQueue();		/*Adiciona um cheque cujas caracteristicas sao lidas do input na fila*/
void processfirstcheck();		/*Processa o cheque mais antigo da file*/
void chequeinfo();				/*Imprime a informacao sobre o cheque cuja referencia e lida do input*/
void processcheck_ref();		/*Processa o cheque cuja referencia e lida do input*/ 
void clienteinfo();				/*Imprime a informacao do cliente cuja referencia e lida do input*/
void clienteinfolist();			/*Imprime a informacao de todos os clientes activos no sistema*/

/*------------------------------------Código-----------------------------------*/

int main(){
	
	char command[COMMANDLEN];

	initT();					/*Inicializa a arvore de clientes*/
	
	while(1){
		scanf("%s", command);
		if (!strcmp(command, "cheque"))
			addchequetoQueue();
			
		else if (!strcmp(command, "processa"))
			processfirstcheck();
		
		else if (!strcmp(command, "processaR"))
			processcheck_ref();
		
		else if (!strcmp(command, "infocheque"))
			chequeinfo();
		
		else if (!strcmp(command, "infocliente"))
			clienteinfo();
		
		else if (!strcmp(command, "info"))
			clienteinfolist();
		
		else if (!strcmp(command, "sair")){
			int ncl;
			ncl = clientesactivos();
			printf("%d %d %d\n", ncl, nch, vch);
			erasequeue();			/*Apaga todos os cheques da fila assim como os nodes que os contêm*/
			erasetree();		/*Apaga todos os clientes da arvore assim como os nodes que os contêm*/
			return EXIT_SUCCESS;
		}
		else
			printf("ERRO: Comando desconhecido\n");
	}
}

void addchequetoQueue(){
	/*addchequetoQueue : {} -> {} 
	  Nao recebe qualquer tipo de argumento. Aloca memoria para colocar o cheque na 
	  fila, do qual fara scan de seguida, incrementa o numero de cheques por processar
	  e adiciona o valor desse cheque ao valor total por processar. Actualiza a arvore
	  de clientes com as informacoes recebidas.*/
	
	Cheque *cheque = malloc(sizeof(Cheque));
	scanf("%d %ld %ld %ld", &cheque->valor, &cheque->refe, &cheque->refb, &cheque->refc);
	nch++;
	vch += cheque->valor;
	treeUpdate(cheque->refe, cheque->refb, cheque->valor);	/*Realiza o update da arvore com
															  os dados do novo cheque*/
	queueput(cheque);

}

void processfirstcheck (){
	/*processfirstcheck : {} -> {} 
	  Nao recebe qualquer tipo de argumento. Verfica se a fila esta vazia e caso nao
	  esteja, processa o primeiro cheque introduzido na fila que esteja por processar,
	  actualiza o numero de cheques por processar, o seu valor e a arvore de clientes.
	  Liberta a memoria alocada correspondente ao cheque processado.*/
	
	Cheque *cheque;
	if (queueempty())
		printf("Nothing to process\n");
	else{
		cheque = queueget();		/*Vai buscar o cheque mais antigo da fila, libertando o node que o contem*/
		nch--;
		vch -= cheque->valor;
		treeUpdate(cheque->refe, cheque->refb, -(cheque->valor));	/*Realiza o update da arvore com
																	  os dados do novo cheque mas com
																	  o seu valor negativo*/
		free(cheque);
	}
}

void processcheck_ref(){
	/*processcheck_ref : {} -> {} 
	  Nao recebe qualquer tipo de argumento. Faz scan da referencia do cheque que
	  quer processar e chama a funcao queuedeletebyref para apagar o node que contém
	  o cheque e coloca o seu endereco de memoria na variavel cheque, caso o cheque
	  exista.Se o cheque nao existir sera feito um print, caso contrario a arvore de
	  clientes sera actualizadae actualiza o numero de cheques por processar e o seu
	  valor e a arvore de clientes. Libertaa memoria alocada correspondente ao cheque 
	  processado.*/
	
	Cheque *cheque;
	long ref;
	scanf("%ld", &ref);
	cheque = queuedeletebyref(ref);		/*Apaga o node que tem o cheque de referencia
										  ref devolve o *cheque*/
	if ((cheque == NULL))
		printf("Cheque %ld does not exist\n", ref);
	else{
		treeUpdate(cheque->refe, cheque->refb, -(cheque->valor));		/*Realiza o update da arvore com
																	  os dados do novo cheque mas com
																	  o seu valor negativo*/
		nch--;
		vch -= cheque->valor;
		free(cheque);
	}
}

void chequeinfo(){
	/*chequeinfo : {} -> {} 
	  Nao recebe qualquer tipo de argumento. Faz scan da referencia do cheque do qual
	  se quer a informacao e chama a funcao queuegetvyref que devolve o endereco de 
	  memoria onde o cheque se encontra caso ele exista e faz print das informacoes do cheque.*/
	
	Cheque *cheque;
	long ref;
	scanf("%ld", &ref);
	cheque = queuegetbyref(ref);	/*Vai buscar o *cheque cuja referencia é ref*/
	if (cheque != NULL)
		printf("Cheque-info: %ld %d %ld --> %ld\n", ref, cheque->valor, cheque->refe, cheque->refb);
}

void clienteinfo(){
	/*clienteinfo : {} -> {} 
	  Nao recebe qualquer tipo de argumento. Faz scan da referencia do cliente do qual
	  se quer a informacao e chama a funcao treenodeinfo que imprime a informacao do cliente.*/
	
	long ref;
	scanf("%ld", &ref);
	treenodeinfo(ref);
}

void clienteinfolist (){
	/*clienteinfolist : {} -> {}
	  Nao recebe qualquer tipo de argumento. Imprime a informacao de todos os clientes
	  activos no sistema*/
	
	Fulltree();
}