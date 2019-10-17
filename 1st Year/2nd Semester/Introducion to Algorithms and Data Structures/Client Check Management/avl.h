#ifndef _avl_
#define _avl_
#include <stdlib.h>
#include <stdio.h>
#include "clientes.h"

typedef struct Avlnode* linkT;

typedef struct Avlnode{ 
	Cliente *cliente;
	linkT l, r; 
	int height;
} Avlnode;

void initT();
linkT newNodeT(Cliente *cliente, linkT l, linkT r);
linkT insertR(linkT h, Cliente *cliente);
linkT AVLbalance(linkT h);
int Balance(linkT h);
linkT rotL(linkT h);
linkT rotR(linkT h);
linkT rotRL(linkT h);
linkT rotLR(linkT h);
void treeUpdate(long refe, long refb, int valor);
void treenodeinfo(long ref);
int clientesactivos();
void traverse(linkT h);
void Fulltree();
void visit(linkT h);
void erasetree();
void eraseallcontentt(linkT h);

#endif