#include <stdlib.h>
#include "queue.h"
#include "cheques.h"

static linkQ head, tail; 

linkQ newNode (Cheque *cheque, linkQ next){
	/*newNode : ptr, link -> link
	  Cria um novo Node Recebendo o "Conteudo" e referenciando um outro node*/
	  
	linkQ x = (linkQ) malloc(sizeof(struct queuenode));
	x->cheque = cheque;
	x->next = next;

 	return x;
}

void queueinit (){
	/*queueinit : {} ->{}
	  Inicia uma Queue (FIFO)*/
	  
	head = NULL;
	tail = NULL;
}

int queueempty (){
	/*queueempty : {} -> int
	  Teste: Verifica se a Queue está vazia*/
	  
	return head == NULL;
}

void queueput (Cheque *cheque){
	/*queueput : ptr -> {}
	  Insere um novo Node na Queue*/
	
	if (head == NULL) {
		tail = newNode(cheque, head);
		head = tail;
 		return;
	}
	tail->next = newNode(cheque, tail->next);
	tail = tail->next;
}

Cheque* queueget (){
	/*queueget : {} -> ptr
	  "Processa" a head da Queue passando o 2º elemento a ser a head*/
	
	Cheque *cheque = head->cheque;
	linkQ t = head->next;
 	free(head);
 	head = t;
 	return cheque;
}

Cheque* queuegetbyref (long ref){
	/*queuegetbyref : long int -> ptr
	  Procura um cheque na Queue por referencia*/	
	  
	Cheque *cheque;
	linkQ x = head;
	while (x != NULL){
		if (x->cheque->refc == ref){
			cheque = x->cheque;
			return cheque;
		}
		else
			x = x->next;
	}
	return NULL;
}

Cheque* queuedeletebyref (long ref){
	/*queuedeletebyref : long int -> ptr
	  Elimina um node da Queue por referencia do seu cheque devolvendo o cheque nele contido*/
	
	Cheque *cheque;
	linkQ x, anterior=NULL;
	
	for(x=head; x != NULL;anterior = x, x=x->next){
		if (x->cheque->refc==ref){
			if (anterior == NULL) {
				/* Esta no inicio */
				if (x->next == NULL ){ 
					/* Um unico elemento*/
					head=NULL;
					tail=NULL;
					cheque = x->cheque;
					free(x);
					return cheque;
				}
				cheque=x->cheque;
				head=x->next;
				free(x);
				return cheque;
			}
			
			else {
				if (x->next==NULL){/* Esta no fim */
					tail=anterior;
					anterior->next=NULL;
					cheque=x->cheque;
					free(x);
					return cheque;
				}
			
				else{
					anterior->next=x->next;
					cheque=x->cheque;
					free(x);
					return cheque;
				}
			}
		}
	}
	
	return NULL;
}

void erasequeue (){
	eraseAllcontentQ(head);
}

void eraseAllcontentQ(linkQ h){
	if (h == NULL){
		return;
	}
	else{
		linkQ next = h->next;
		free(h->cheque);
		free(h);
		eraseAllcontentQ(next);
	}
}