#include <stdlib.h>
#include "clientes.h"
#include "avl.h"

static linkT head;
static int nclA = 0;	/*Numero de clientes activos*/

void initT (){
	/*initT : {} -> {} 
	  Nao recebe qualquer tipo de argumento. Inicializa uma nova arvore de clientes.*/
	
	head = NULL;
}

linkT newNodeT(Cliente *cliente, linkT l, linkT r){
	/*newNodeT : ptr, link, link -> link
	  Recebe um ponteiro e dois links. Cria um novo node cujas caracteristicas
	  sao passadas no argumento e devolve um link para esse mesmo node*/
	
	linkT x = (linkT)malloc(sizeof(Avlnode));
	x->cliente = cliente;
	x->l = l;
	x->r = r;
	x->height=1;
	return x;
} 

int height (linkT h){
	/*height : link -> int
	  Recebe um link do qual ira ver a altura.*/
	
	if (h == NULL)
		return 0;
	return h->height;
}

int Balance (linkT h){
	/*Balance : link -> int
	  Recebe um link do qual calcula o equilibrio.*/
	  
	if (h == NULL)
		return 0;
	return height(h->l) - height(h->r);
} 

linkT rotL (linkT h){
	/*rotL : link -> link
	  Realiza uma rotacao a esquerda da arvore cuja raiz é h.*/
	
	int height_left, height_right;
 	linkT x = h->r;
 	h->r = x->l;
 	x->l = h;
 	height_left = height(h->l);
	height_right = height(h->r);
 	h->height = height_left > height_right ? height_left + 1 : height_right + 1;
	height_left = height(x->l);
	height_right = height(x->r);
	x->height = height_left > height_right ? height_left + 1 : height_right + 1;
	return x;
}

linkT rotR (linkT h){
	/*rotR : link -> link
	  Realiza uma rotacao a direita da arvore cuja raiz é h.*/
	
	int height_left, height_right;
	linkT x = h->l;
	h->l = x->r;
	x->r = h;
	height_left = height(h->l);
	height_right = height(h->r);
	h->height = height_left > height_right ? height_left + 1 : height_right + 1;
	height_left = height(x->l);
	height_right = height(x->r);
	x->height =	height_left > height_right ? height_left + 1 : height_right + 1;
 	return x;
}

linkT rotLR (linkT h){
	/*rotLR : link -> link
	  Realiza uma rotacao a direita da arvore cuja raiz é h seguida de uma rotação
	  a direita.*/
	
	if (h == NULL) 
		return h;
 	h->l = rotL(h->l);
 	return rotR(h);
}

linkT rotRL (linkT h){
	/*rotRL : link -> link
	  Realiza uma rotacao a esquerda da arvore cuja raiz é h seguida de uma rotação
	  a direita*/
	
 	if (h == NULL) 
 		return h;
 	h->r = rotR(h->r);
 	return rotL(h);
}

linkT AVLbalance (linkT h){
	/*AVLbalance : link -> link
	  Equilibra a arvore.*/
	  
	int balanceFactor;

	if (h == NULL) 
		return h;

	balanceFactor = Balance(h);

	if(balanceFactor > 1) {
 		if (Balance(h->l) > 0) h = rotR(h);
		else h = rotLR(h);
	}

 	else if(balanceFactor < -1){
 		if (Balance(h->r) < 0) h = rotL(h);
 		else h = rotRL(h);
 	}

 	else{
		int height_left = height(h->l);
		int height_right = height(h->r);
		h->height = height_left > height_right ? height_left + 1 : height_right + 1;
 	}
 return h;
}

linkT insertR (linkT h, Cliente *cliente){
	/*insertR : link, ptr -> link
	  Insere um novo node na arvore cujo cliente é passado através dos argumentos 
	  e devolve um link para esse mesmo node*/
	  
 	if (h == NULL)
 		return newNodeT(cliente, NULL, NULL);
 	if (cliente->refC< h->cliente->refC)
 		h->l = insertR(h->l, cliente);
 	else
 		h->r = insertR(h->r, cliente);
 	h = AVLbalance(h);
 	return h;
} 

linkT search (linkT h, long ref){
	/*search : link, long int -> link*/
	
	if (h == NULL)
		return NULL;
	if ( ref == h->cliente->refC )
		return h;
	if ( ref < h->cliente->refC )
		return search(h->l, ref);
 	else
		return search(h->r, ref);

} 

void treeUpdate (long refe, long refb, int valor){
	/*treeUpdate : long int, long int, int -> {}
	  Realiza o update da tree com as informações passadas nos argumentos*/
	
	linkT nodeE, nodeB;
	nodeE = search(head,refe);
	if (nodeE == NULL){
		Cliente *cliente = malloc(sizeof(Cliente));
		cliente->refC = refe;
		cliente->vche = valor;
		cliente->nche = 1;
		cliente->vchb = 0;
		cliente->nchb = 0;
		head = insertR(head,cliente);
		nclA++;
	}
	else{
		
		if (valor >= 0){					/*Se estamos a adicionar um cheque*/
			if (nodeE->cliente->vchb == 0 && nodeE->cliente->vche == 0)
				nclA++;
			nodeE->cliente->vche += valor;
			nodeE->cliente->nche++;
		}
		else{								/*Se estamos a processar um cheque*/
			nodeE->cliente->vche += valor;
			nodeE->cliente->nche--;
			if (nodeE->cliente->nche == 0 && nodeE->cliente->nchb == 0)
				nclA--;
		}
	}

	nodeB = search(head,refb);
	if (nodeB == NULL){
		Cliente *cliente = malloc(sizeof(Cliente));
		cliente->refC = refb;
		cliente->vchb = valor;
		cliente->nchb = 1;
		cliente->vche = 0;
		cliente->nche = 0;
		head = insertR(head,cliente);
		nclA++;
	}
	else{
		
		if (valor >= 0){					/*Se estamos a adicionar um cheque*/
			if (nodeB->cliente->vchb == 0 && nodeB->cliente->vche == 0)
				nclA++;
			nodeB->cliente->vchb += valor;
			nodeB->cliente->nchb++;
		}
		else{								/*Se estamos a processar um cheque*/
			nodeB->cliente->vchb += valor;
			nodeB->cliente->nchb--;
			if (nodeB->cliente->nche == 0 && nodeB->cliente->nchb == 0)
					nclA--;
			}
	}
}

void treenodeinfo (long ref){
	/*treenodeinfo : long int -> {}
	  Imprime a informação de um cliente cuja referencia é ref*/
	
	linkT nodeRef;
	nodeRef = search(head,ref);
	printf("Cliente-info: %ld %d %d %d %d\n", ref, nodeRef->cliente->nche, nodeRef->cliente->vche, nodeRef->cliente->nchb, nodeRef->cliente->vchb);
}

void printall (linkT h){
	/*printall : link -> {}
	  Imprime as informações dos clientes por ordem crescente de referencia*/
	  
	if (h == NULL)
		return;
 	printall(h->l);
 	visit(h);
 	printall(h->r);
}

void visit (linkT h){
	/*visit : link -> {}
	  Imprime a informação do cliente que se encontra no node h*/
	  
	if (h->cliente->vche!=0||h->cliente->vchb!=0)
		printf("*%ld %d %d %d %d\n",h->cliente->refC,h->cliente->nche,h->cliente->vche,h->cliente->nchb,h->cliente->vchb);
}

int clientesactivos (){
	/*clientesactivos : {} -> int
	  Devolve o numero de clientes activos na arvore*/
	return nclA;
}

void Fulltree (){
	/*Fulltree : {} -> {}
	  Chama a função que imprime as informações dos clientes*/
	
	if (nclA == 0)
		printf("No active clients\n");
	else 
		printall(head);
}

void erasetree(){
	eraseallcontentt(head);
}

void eraseallcontentt (linkT h){
	/*eraseAllcontentT : link -> {}
	  Elimina toda a informação de uma arvore assim como arvore em si*/
	  
	if (h == NULL){
		return;
	}
	else{
		Cliente *cliente;
		cliente = h->cliente;
		free(cliente);
		eraseallcontentt(h->r);
		eraseallcontentt(h->l);
		free(h);
	}
}