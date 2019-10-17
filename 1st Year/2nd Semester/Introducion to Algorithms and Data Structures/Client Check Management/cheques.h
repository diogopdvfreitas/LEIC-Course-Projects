#ifndef _cheques_
#define _cheques_
#include <stdio.h>
#include <stdlib.h>

/*Um cheque é uma estrutura constituida pelo valor do cheque(valor), 
a referencia do emissor(refe), do beneficiario(refb), e do cheque em si(refc)*/

typedef struct{
	int valor;
	long refe, refb, refc;
} Cheque;

#endif