#ifndef _clientes_
#define _clientes_
#include <stdio.h>
#include <stdlib.h>

/*Um cliente é uma estrutura constituida pelo numero da referencia do cliente(refC),
pelo numero de cheques dos quais é emissor(nche) e beneficiario(nchb), assim como os seus
valores totais (vche e vchb respectivamente)*/

typedef struct{
	long refC;
	int nche, vche, nchb, vchb;
} Cliente;

#endif