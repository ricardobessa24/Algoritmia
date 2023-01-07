#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

#define _CRT_SECURE_NO WARNINGS

typedef struct Node {
	int data;
	struct Node* next;
}NODE;



void printList(NODE* lista);
void InserirInicio(NODE** lista, int valor);
void InserirFim(NODE** lista, int valor);
//NODE* -> Dá o ponteiro do nó, NODE** -> Dá o endereço desse ponteiro
void ApagarNo(NODE** lista, int valor);
void ApagarLista(NODE** lista);

int main() {
	NODE* inicio = NULL;
	NODE* segundo = NULL;
	NODE* terceiro = NULL;
	NODE* temp = NULL;
	

	//alocar a memória para cada node
	inicio = (NODE*)malloc(sizeof(NODE));
	segundo = (NODE*)malloc(sizeof(NODE));
	terceiro = (NODE*)malloc(sizeof(NODE));

	inicio->data = 1;
	inicio->next = segundo;

	segundo->data = 2;
	segundo->next = terceiro;

	terceiro->data = 3;
	terceiro->next = NULL;


	//inserir no início
	//	NODE* novo_no = NULL;
	//	novo_no = (NODE*)malloc(sizeof(NODE));
	//	novo_no->data = 4;
	//	novo_no->next = inicio;
	//	inicio = novo_no;
	


	//mostrar os valores da lista
	printList(inicio);
	//inserir no início
	InserirInicio(&inicio, 23);
	//mostrar os valores da lista
	printList(inicio);
	//inserir Fim
	InserirFim(&inicio, 24);
	//mostrar os valores da lista
	printList(inicio);
	//apagar no
	ApagarNo(&inicio, 3);
	//mostrar os valores da lista
	printList(inicio);
	ApagarLista(&inicio);
	printList(inicio);




}

void printList(NODE * list)
{
	if (list == NULL) {
		printf("\nLista vazia");
		return;
	}
	printf("\n LISTA -> ");
	while (list != NULL)
	{
		printf("%d -> ", list->data);
		list = list->next;
	}
}

void InserirInicio(NODE** lista, int valor)
{
	//alocar memória para novo no

	NODE* novo_no = (NODE*)malloc(sizeof(NODE));
	novo_no->data = valor;
	//tornar o novo nó como primeiro
	novo_no->next = *lista;
	*lista = novo_no;

}


void InserirFim(NODE** lista, int valor)
{
	//criar novo nó
	NODE* novo_no = (NODE*)malloc(sizeof(NODE));

	NODE* temp = *lista;

	//guardar o valor
	novo_no->data = valor;
	//como vai ser o último
	novo_no->next = NULL;

	//verificar se a lista está vazia, se sim o novo nó será o inicio
	if (*lista == NULL)
	{
		*lista = novo_no;
		return;
	}
	//percorrer a lista até encontrar o último
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	//mudar o next para o novo nó
	temp->next = novo_no;
	return;

}

void ApagarNo(NODE** lista, int valor)
{
	NODE* prev=NULL, *temp;
	temp = *lista; 

	if (temp != NULL && temp->data == valor)
	{
		*lista = temp->next;
		free(temp); //libertar a memória
	}
	//encontrar o nó que tem o valor a encontrar
	while (temp != NULL && temp->data != valor) {
		prev = temp;
		temp = temp->next;
	}
	//verificar se encontrou o valor
	if (temp == NULL)
		return;

	//se encontrou
	prev->next = temp->next;

	free(temp);
}

void ApagarLista(NODE** lista)
{
	NODE* temp = *lista;
	NODE* seguinte=NULL;
	while (temp != NULL) {
		seguinte = temp->next;
		free(temp);
		temp = seguinte;
	}
	*lista = NULL;
	if (lista = NULL)
	{
		printf("\t---Lista Vazia!---");
	}
}





