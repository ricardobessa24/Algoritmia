// ER_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

//Defininir tipo para Enumerar valores a ser usados
typedef enum _Boolean{FALSE=0, TRUE=1}BOOLEAN;

//Fun��o retorna endere�o para inteiro
int* MemoryAlloc(int dim);
//ler array modo din�mico
void ReadArray(int* w, int dim);// (valor de inteiros e dimens�o destes)

int main()
{
    //BOOLEAN a;
    //a = TRUE;
    //printf("Hello World!\n");

    int dim, i, * v = NULL; //*v valor de um inteiro
    printf("Dimens�o de um vetor:");
    scanf_s("%d", &dim); // & -> endere�o da variavel porque est� fora da fun��o

    //Alocar mem�ria
    if ((v = MemoryAlloc(dim)) == NULL)
        printf("Erro na aloca��o de mem�ria");
    else {
        ReadArray(v, dim);
        for (i = 0; i < dim; i++) {
            printf("V[%d] = %d \n", i, v[i]); //*(v+i)
        }
        //Libertar mem�ria que foi alocada
        free(v);
    }
}

int* MemoryAlloc(int xpto) {
    int* w = NULL;
    w = (int*)malloc(xpto * sizeof(int));
    return w;
}

void ReadArray(int* w, int dim) {

    for (int i = 0; i < dim; i++) {
        printf("V[%d] = ", i);
        scanf_s("%d", w[i]);
    }
}
