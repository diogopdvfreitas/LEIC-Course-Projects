/*Introdução a Algoritmos e Estruturas de Dados, Projecto 1*/

/*
Diogo Freitas   81586 
Nuno Cartier    81718
Pedro Caldeira  81888
*/

/*---------------Bibliotecas, Constantes, Estruturas e Variáveis----------------*/

#include <stdio.h>
#include <stdlib.h>

#define GOOD 1
#define BAD 0
#define MAXMEMBERS 1000
#define NAMELEN	42

typedef struct{
	int ref, eval, inP, outP, outV, outVM, inV, inVM, partners;
	char name[NAMELEN];
}Bank;

Bank bank_lib[MAXMEMBERS];

int matrix[MAXMEMBERS][MAXMEMBERS];		/*Matriz de transações*/
int count_banks = 0;
int good_banks = 0;

/*--------------------------------Protótipos------------------------------------*/

void add_bank();						/*Adiciona um novo banco à biblioteca (bank_lib) de bancos.*/
void declassify();						/*Atribui uma classificacao má a um banco.*/
void promote();							/*Atribui uma classificacao boa a um banco.*/
void loan();							/*Realiza um empréstimo entre 2 bancos.*/
void payment();							/*Realiza uma amortização de um empréstimo.*/
int search_bank_position(int refer);	/*Procura um banco pela sua referência na 
										biblioteca de bancos e devolve a sua posição na mesma.*/
void list();							/*Chama uma das funções de listagem.*/
void short_list();						/*Escreve na janela uma lista simplificada da rede.*/
void full_list();						/*Escreve na janela uma lista completa da rede.*/
void histogram();						/*Escreve na janela uma lista com o numero de bancos 
										que têm x parceiros.*/
void update_values();					/*Actualiza os valores relativos a cada banco.*/
void declassify_worse();				/*Atribui uma classificação má ao banco com classificação
										boa que mais dinheiro tem emprestado a bancos com
										classificação má.*/

/*------------------------------------Código-----------------------------------*/

int main(){
	char command;
	while(1){
		command = getchar();
		switch(command){
		case 'a':
			add_bank();	
			break;
		
		case 'k':
			declassify();
			break;
		
		case 'r':
			promote();
			break;
		
		case 'e':
			loan();
			break;
		
		case 'p':
			payment();
			break;

		case 'l':
			list();
			break;
			
		case 'K':
			declassify_worse();
			break;

		case 'x':
			printf("%d %d\n", count_banks, good_banks);
			return EXIT_SUCCESS;
		
		default:
			printf("ERRO: Comando desconhecido\n");
		}
		while ((command = getchar()) != '\n');

	}
return EXIT_FAILURE;
}

void add_bank(){
/*add_bank : {} -> {} Não recebe qualquer tipo de argumento. Faz scan do ecrã as 
  características de uma novo banco e adiciona-o à biblioteca de bancos. 
  Não gera qualquer tipo de output.*/

	Bank bank;
	
	scanf("%s%d%d", bank.name, &bank.eval, &bank.ref);
	bank.inV = 0; bank.inVM = 0; bank.outV = 0; bank.outVM = 0; bank.inP = 0; bank.outP = 0; bank.partners = 0;
	if (bank.eval == 1)
		good_banks++;
	
	bank_lib[count_banks] = bank;
	count_banks++;
}

void declassify(){
/*declassify : {} -> {} Não recebe qualquer tipo de argumento. Faz scan do ecrã
  da referência de um banco e caso tenha uma boa avaliação atribui-lhe uma má.
  Não gera qualquer tipo de output.*/
	
	int refer, i;
	
	scanf("%d", &refer);
	i = search_bank_position(refer);
	if (bank_lib[i].eval == GOOD)
	{
		bank_lib[i].eval = BAD;
		good_banks--;
	}
}

void promote(){
/*promote : {} -> {} Não recebe qualquer tipo de argumento. Faz scan do ecrã da 
  referência de um banco e caso tenha uma má avaliação atribui-lhe uma boa.
  Não gera qualquer tipo de output.*/

	int refer, i;
	
	scanf("%d", &refer);
	i = search_bank_position(refer);
	if (bank_lib[i].eval == BAD)
	{
		bank_lib[i].eval = GOOD;
		good_banks++;
	}
}

void loan(){
/*loan : {} -> {} Não recebe qualquer tipo de argumento. Faz scan do ecrã das
  referências de dois bancos e o valor do empréstimo.
  Realiza o empréstimo entre os dois bancos.
  Não gera qualquer tipo de output.*/
  
	int ref1, ref2, value, pos1, pos2;

	scanf("%d%d%d", &ref1, &ref2, &value);
	pos1 = search_bank_position(ref1);
	pos2 = search_bank_position(ref2);
	if ((matrix[pos1][pos2] == 0) && (matrix[pos2][pos1] == 0)){
		bank_lib[pos1].partners++;
		bank_lib[pos2].partners++;
	}
	matrix[pos1][pos2] += value;
	bank_lib[pos1].outV += value;
	bank_lib[pos2].inV += value;
}

void payment(){
/*payment : {} -> {} Não recebe qualquer tipo de argumento. Faz scan do ecrã
  das referências de dois bancos e de um valor que será amortizado do empréstimo
  ocorrido entre os ditos bancos.
  Não gera qualquer tipo de output.*/
	
	int ref1, ref2, value, pos1, pos2;
	
	scanf("%d%d%d", &ref1, &ref2, &value);
	pos1 = search_bank_position(ref1);
	pos2 = search_bank_position(ref2);

	if (value <= matrix[pos2][pos1])
	{
		matrix[pos2][pos1] -= value;

		if ((matrix[pos1][pos2] == 0) && (matrix[pos2][pos1] == 0))
		{
			bank_lib[pos1].partners--;
			bank_lib[pos2].partners--;
		}
	}
}

int search_bank_position(int refer){
/*search_bank_position: int -> int Recebe uma referência como input,
  descobrindo em que posição o banco com a mesma referência se encontra
  posicionado.
  Tem como output a posição do banco com  essa referência*/
	int i;

	for (i = 0; i < count_banks; i++){
		if (bank_lib[i].ref == refer)
			return i;
	}
	return 0;
}

void list(){
/*list : {} -> {} Não recebe qualquer tipo de argumento. Faz scan do ecrã de um 
  número que definirá que género de lista será gerada e escrita na janela através
  do uso de outra função.
  Não gera qualquer tipo de output.*/
	
	int type;

	scanf("%d", &type);
	if (type == 0)
		short_list();
	else if (type == 1)
		full_list();
	else if (type == 2)
		histogram();
}

void short_list(){
/*short_list : {} -> {} Não recebe qualquer tipo de argumento. Escreve na janela uma
  lista simplificada da rede de bancos existente.
  Não gera qualquer tipo de output.*/
	
	int i;
	
	for (i = 0; i < count_banks; i++)
		printf("%d %s %d\n", bank_lib[i].ref, bank_lib[i].name, bank_lib[i].eval);
}

void full_list(){
/*full_list : {} -> {} Não recebe qualquer tipo de argumento. Esreve na janela uma 
  lista completa e com todos os dados actualizados da rede de bancos existente
  e escreve-a na janela.
  Não gera qualquer tipo de output.*/
	
	int i;

	update_values();
	for (i = 0; i < count_banks; i++)
		printf("%d %s %d %d %d %d %d %d %d\n", bank_lib[i].ref, bank_lib[i].name, bank_lib[i].eval, bank_lib[i].inP,
					 						   bank_lib[i].outP, bank_lib[i].outV, bank_lib[i].outVM, bank_lib[i].inV, bank_lib[i].inVM);
}

void histogram(){
/*histogram : {} -> {} Não recebe qualquer tipo de argumento. Gera uma lista que dá
  informação sobre o número de bancos que têm x parceiros e escreve-a na janela, 
  caso nenhum banco tenha um certo número de parceiros essa informação não é
  escrita na janela.
  Não gera qualquer tipo de output.*/

	int partn[MAXMEMBERS], i, j;

	for (i = 0; i < count_banks; i++){
		partn[i] = 0;
		for (j = 0; j < count_banks; j++)
		{
			if (bank_lib[j].partners == i)
				partn[i]++;
		}
		if (partn[i] != 0)
			printf("%d %d\n", i, partn[i]);
	}		
}

void update_values(){
/*update_values: {} -> {} Não recebe qualquer tipo de argumento. Actualiza os
  valores caracteristicos de cada banco através da matriz de valores.
  Não gera qualquer tipo de output.*/
	
	int i, j;

	for (i = 0; i < count_banks; i++){
		bank_lib[i].inP = 0; bank_lib[i].outP = 0; bank_lib[i].outV = 0; bank_lib[i].outVM = 0; bank_lib[i].inV = 0; bank_lib[i].inVM = 0;
}
	for (i = 0; i < count_banks; i++){
		for (j = 0; j < count_banks; j++){
		
			if (matrix[i][j] != 0){
				bank_lib[i].outP++;
				bank_lib[j].inP++;
				bank_lib[i].outV += matrix[i][j];
				bank_lib[j].inV += matrix[i][j];
				if (bank_lib[j].eval == BAD)
					bank_lib[i].outVM += matrix[i][j];
				if (bank_lib[i].eval == BAD)
					bank_lib[j].inVM += matrix[i][j];
			}
		}
	}
}

void declassify_worse(){
/*declassify_worse : {} -> {} Não recebe qualquer tipo de argumento. Procura o banco
  com classificação boa que mais dinheiro tem emprestado a bancos maus e atribui-
  -lhe uma classificação má.
  Não gera qualquer tipo de output.*/
	
	int i, value = 1,pos = -1;

	update_values();
	for (i = 0; i < count_banks; i++){
		if (bank_lib[i].eval == 1){
			if (bank_lib[i].outVM >= value){
				value = bank_lib[i].outVM;
				pos = i;
			}
		}
	}
	if (pos != -1){
		bank_lib[pos].eval = BAD;
		good_banks--;
		printf("*%d %s %d %d %d %d %d %d %d\n", bank_lib[pos].ref, bank_lib[pos].name, bank_lib[pos].eval, bank_lib[pos].inP,
												bank_lib[pos].outP, bank_lib[pos].outV, bank_lib[pos].outVM, bank_lib[pos].inV, bank_lib[pos].inVM);
	}		
		printf("%d %d\n", count_banks, good_banks);
}