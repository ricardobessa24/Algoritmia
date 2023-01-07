#pragma warning(disable : 6011)
#pragma warning(disable : 6031)
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct {
	int ano;
	int mes;
	int dia;
}DATA;


typedef struct {
	int numero;
	char nome[50];
	DATA dataNascimento;
}ALUNO;




void main() {
	ALUNO a;
	ALUNO* b;

	a.numero = 1234;
	strcpy(a.nome, "João Pereira");
	a.dataNascimento.ano = 2000;
	a.dataNascimento.mes = 5;
	a.dataNascimento.dia = 20;

	printf("\nNome = %s, \n Numero = %d \nDia = %d, \nMes = %d, \nAno = %d", a.nome, a.numero, a.dataNascimento.dia, a.dataNascimento.mes, a.dataNascimento.ano);

	b = (ALUNO*)malloc(sizeof(ALUNO));
	b->numero = 12;
	strcpy(b->nome, "Manuel Silva");
	b->dataNascimento.dia = 12;
	b->dataNascimento.mes = 1;
	b->dataNascimento.ano = 1999;
	printf("\nNome = %s, \nNumero = %d \nDia = %d, \nMes = %d, \nAno = %d", b->nome, b->numero, b->dataNascimento.dia, b->dataNascimento.mes, b->dataNascimento.ano);

	///////////////

	typedef struct {
		int numero;
		char nome[50];
		DATA* dataNascimento;
	}ALUNOP;


	ALUNOP	x;
	ALUNOP* y;
	DATA d;
	d.dia = 21; d.mes = 10; d.ano = 2000;
	x.numero = 1234;
	strcpy(x.nome, "António Silva");
	x.dataNascimento = &d;
	printf("\nNome = %s, \nNumero = %d \nDia = %d, \nMes = %d, \nAno = %d", x.nome, x.numero, x.dataNascimento->dia,x.dataNascimento->mes, x.dataNascimento->ano );


	y = (ALUNOP*)malloc(sizeof(ALUNOP));
	y->dataNascimento = (DATA*)malloc(sizeof(DATA));
	printf("\nIntroduza os dados do aluno:");
	printf("\tNome : ");
	gets(y->nome);
	printf("\tNumero : ");
	scanf_s("%d", &(y->numero)); //queremos o endereço do número e não o número
	printf("\tDia: ");
	scanf_s("%d", &(y->dataNascimento->dia));
	printf("\tMES: ");
	scanf_s("%d", &(y->dataNascimento->mes));
	printf("\tANO: ");
	scanf_s("%d", &(y->dataNascimento->ano));
	printf("\nNome = %s, \nNumero = %d \nDia = %d, \nMes = %d, \nAno = %d", y->nome, y->numero, y->dataNascimento->dia, y->dataNascimento->mes, y->dataNascimento->ano);



	//////////////////////////////////////////////////////////////////////////////////////////////////////


	/// <summary>
	/// Struct com struct a apontar para a estrutura
	/// </summary>
	typedef struct pessoa {
		char nome[30];
		int idade;
		struct pessoa* pai;
	}PESSOA;

	PESSOA Joao;
	PESSOA* p;
	
	Joao.idade = 23;
	strcpy(Joao.nome, "João da Silva");
	Joao.pai = NULL;

	p = (PESSOA*)malloc(sizeof(PESSOA));
	p->idade = 45;
	strcpy(p->nome, "Pedro da Silva");
	p->pai = NULL;

	Joao.pai = p;

	printf("\nNome = %s\nIdade = %d\nNome do pai %s\n Idade do pai = %d",
		Joao.nome, Joao.idade, Joao.pai->nome, Joao.pai->idade
	);// OU 

	printf("\n%d", sizeof(PESSOA*));

}