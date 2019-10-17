#ifndef _queue_
#define _queue_
#include <stdio.h>
#include "cheques.h"

typedef struct queuenode* linkQ;

/*Um queuenode é uma estrutura constituida por um
apontador para um cheque e um link para o proximo queuenode*/

struct queuenode {
 Cheque *cheque;
 linkQ next;
};

void queueinit();
int queueempty();
void queueput(Cheque* cheque);
Cheque* queueget(); 
Cheque* queuegetbyref(long ref);
Cheque* queuedeletebyref(long ref);
void eraseAllcontentQ(linkQ h);
void erasequeue();
#endif	