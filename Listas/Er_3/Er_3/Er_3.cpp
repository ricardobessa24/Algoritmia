
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
//*v -> ponteiro para inteiros; **v -> ponteiro para ponteiro de inteiros
typedef enum _BOOLEAN {FALSE = 0, TRUE = 1}BOOLEAN;

BOOLEAN MemoryAlloc(int*** v, int size);
void ReadArray(int** v, int size);
void ReadInteger(int* x);



void main() {
	int** v = NULL;
	int size, i;

	printf("Dimensão do vetor: ");
	scanf_s("%d", &size);

	if (MemoryAlloc(&v, size))
	{
		ReadArray(v, size);
		for (i = 0; i < size; i++)
		{
			printf("V[%d] = %d \n", i, *v[i]); //valor de cada vetor **(v+i)
		}
		for (i = 0; i < size; i++)
		{
			free(*(v + i));
		}
		free(v);
	}
	else
		printf("Erro na alocação de memória");

}

BOOLEAN MemoryAlloc(int*** v, int size)
{
	int i, j;
	if ((*v = (int**)malloc(size * sizeof(int*))) == NULL)//v+1 ponteiro para inteiros, tamanho de um endereço de memória 
		return FALSE;
	for(i = 0; i < size; i++)      
		if ((*(*v + i) = (int*)malloc(sizeof(int))) == NULL) //para cada um desses inteiros alocar o valor do inteiro
		{ //Libertar memória
			for (j = i - 1; j >= 0; j--)//quando der erro vir ao para trás
				free(*(*v + j));
			return FALSE;
		}
	return TRUE;
}

void ReadArray(int** v, int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		printf("v[%d]: ", i);
		ReadInteger(*(v + i));
	}
}

void ReadInteger(int* x)
{
	printf("Introduza um inteiro: ");
	scanf_s("%d", x);
}