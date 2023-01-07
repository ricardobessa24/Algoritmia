#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <locale.h>
#pragma warning(disable : 4996)

typedef enum _BOOLEAN { FALSE = 0, TRUE = 1 } BOOLEAN;

typedef struct _CLIENT {
	int client_code;
	char name[100];
}CLIENT;

int ReadClients(CLIENT**, char*); //passar o ponteiro dos pontrios para clientes, e ponteiro para caracteres

void main(void)
{
	int num_clients, i;
	CLIENT* clients = NULL;
	char str[100];//variavel 100 caracteres

	printf("\nNome do ficheiro : ");
		scanf_s("%s", str);

	switch (num_clients = ReadClients(&clients, str)) //ReadClients(vetor clientes e nome do ficheiro)
	{
	case -2: printf("\a\nErro na alocação de memória...\n");
		break;
	case -1: printf("\a\nErro de leitura do ficheiro...\n");
		break;
	case 0: printf("\a\nFicheiro vazio...\n");
		break;
	default: printf("\nFicheiro lido com sucesso...\n");
		printf("\nConteúdo do ficheiro:\n");
		for (i = 0; i < num_clients; i++)
			printf("%d ; %s\n", clients[i].client_code, clients[i].name);//aceder aos clientes no vetor clientes, ir buscar o client_code e name
	}
	free(clients);

}

int ReadClients(CLIENT** v, char* filename)
{
	FILE* fp;
	int size = 0;
	if ((fp = fopen(filename, "rt")) == NULL)
		return(-1);
	while (!feof(fp))
	{
		if ((*v = (CLIENT*)realloc(*v, sizeof(CLIENT) * (size + 1))) == NULL) //realloc faz uma cópia e acrescenta mais bytes, com o tamanho = size +1
			return(-2);
		fscanf(fp, "%d;%[^\n]s", &((*v + size)->client_code), (*v + size)->name);//ler até encontrar /n
		size++;
	}
	fclose(fp);
	return(size);
}