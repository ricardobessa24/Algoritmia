
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

//Defininir tipo para Enumerar valores a ser usados
typedef enum _Boolean { FALSE = 0, TRUE = 1 }BOOLEAN;
typedef enum { ERROR = 0, OK = 1 }STATUS;

//Endereço de um ponteiro para inteiros
STATUS MemoryAlloc(int **w,int dim);
void ReadArray(int* w, int dim);// (valor de inteiros e dimensão destes)

int main()
{
    int dim, i, * v = NULL; //*v valor de um inteiro
    printf("Dimensao de um vetor:");
    scanf_s("%d", &dim);

    if (MemoryAlloc(&v, dim) == OK)// esta função tem & por o valor do v vai ser alterado
    {
        ReadArray(v, dim);// aqui só passa o v porque só vai ler o vetor
        for (i = 0; i < dim; i++)
            printf("V[%d] = %d\n", i, v[i]);
        free(v);
    }
    else
        printf("ERRO na alocação de memória");
}

STATUS MemoryAlloc(int** w, int dim) {
    if (( * w = (int*)malloc(dim * sizeof(int))) == NULL)
        return (ERROR);
    return OK;


}

void ReadArray(int* w, int dim)
{
    int i;
    for (i = 0; i < dim; i++)
    {
        printf("\tV[%d]= ", i);
        scanf_s("%d", w + i);
    }
}