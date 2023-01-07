#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _DIR {
	char nome[20];
	int n_fich;
	int n_Kb;
}DIR;

typedef struct _BTREE_NODE
{
	void* data;
	struct _BTREE_NODE* left;
	struct _BTREE_NODE* right;
} BTREE_NODE;

#define DATA(node) ((node)->data)
#define LEFT(node) ((node)->left)
#define RIGHT(node) ((node)->right)
#define EMPTY NULL
#define NO_LINK NULL

typedef BTREE_NODE* BTREE;
typedef enum _BOOLEAN { FALSE = 0, TRUE = 1 } BOOLEAN;
typedef enum _STATUS { ERROR = 0, OK = 1 } STATUS;

BTREE_NODE* InitNode(void* ptr_data, BTREE_NODE* node1, BTREE_NODE* node2);
BTREE_NODE* NewBtreeNode(void* data);
void BtreeFree(BTREE btree);
BTREE_NODE* CreateBtree(void** v, int i, int size);
void PrintDirM100(BTREE btree);
int CountTotalFiles(BTREE btree, char* directoryname);
int CountPrintEmptyDirs(BTREE btree);
STATUS ReadFile(void** depts, char* file_name);
void Maiscemfiles(BTREE);
void ShowDiretoria(BTREE);
int MostrarTotalkb(BTREE btree, char* name);
int CountEmptyDir(BTREE btree);
void showEmptyDir(BTREE);

int main()
{
	BTREE btree;
	void* dirs[15];
	char file_name[20];
	char dir_name[20];
	//printf("Nome do ficheiro: ");
	//scanf("%s", file_name);
	if (ReadFile(dirs, "Dir.txt"))
	{
		btree = CreateBtree(dirs, 0, 15);

		printf("As diretorias com mais de 1000 kbytes sao: \n");

		Maiscemfiles(btree);

		printf("Insira a diretoria:");
		scanf("%s", &dir_name);
		//printf("O total de ficheiros da diretoria e: %d", CountTotalFiles(btree, dir_name));
		printf("O total de ficheiros da diretoria e : %d \n", MostrarTotalkb(btree, dir_name));
		printf("O total de diretorias vazias sao: %d \n", CountEmptyDir(btree));
		showEmptyDir(btree);
	
		system("pause");
	}
	else
		printf("ERRO na leitura do ficheiro\n");
	system("pause");
	return 0;
}

BTREE_NODE* CreateBtree(void** v, int i, int size)
{
	if (i >= size)
		return(NULL);
	else
		return(InitNode(*(v + i), CreateBtree(v, 2 * i + 1, size), CreateBtree(v, 2 * i + 2, size)));
}

BTREE_NODE* InitNode(void* ptr_data, BTREE_NODE* node1, BTREE_NODE* node2)
{
	BTREE_NODE* tmp_pt = NULL;
	tmp_pt = NewBtreeNode(ptr_data);
	LEFT(tmp_pt) = node1;
	RIGHT(tmp_pt) = node2;
	return(tmp_pt);
}

void Maiscemfiles(BTREE btree)
{
	int max = 1000;

	if (btree != NULL)
	{
		Maiscemfiles(LEFT(btree));
		if ((((DIR*)DATA(btree))->n_Kb) > max)
			ShowDiretoria(btree);
		Maiscemfiles(RIGHT(btree));
	}
}

void ShowDiretoria(BTREE btree)
{
	if (btree != NULL)
	{
		printf("A diretoria %s tem %d ficheiros e um total de %d kbytes \n", ((DIR*)DATA(btree))->nome, ((DIR*)DATA(btree))->n_fich, ((DIR*)DATA(btree))->n_Kb);
	}
}

int MostrarTotalkb(BTREE btree, char* dir_name)
{
	int count = 0;
	if (btree != NULL) 
	{
		if (!(strcmp(((DIR*)DATA(btree))->nome, dir_name)))
			count += ((DIR*)DATA(btree))->n_fich + ((DIR*)DATA(LEFT(btree)))->n_fich + ((DIR*)DATA(RIGHT(btree)))->n_fich;
		count += MostrarTotalkb(LEFT(btree), dir_name) + MostrarTotalkb(RIGHT(btree), dir_name);
	}
	return (count);
}



int CountEmptyDir(BTREE btree)
{
	int count = 0;
	if (btree != NULL)
	{
		if (((DIR*)DATA(btree))->n_fich == 0)
			count += 1;
		count += CountEmptyDir(LEFT(btree)) + CountEmptyDir(RIGHT(btree));
	}

	return count;
}

void showEmptyDir(BTREE btree)
{
	if (btree != NULL)
	{
		showEmptyDir(LEFT(btree));
		if (((DIR*)DATA(btree))->n_fich == 0)
			ShowDiretoria(btree);
		showEmptyDir(RIGHT(btree));
		
	}
}



























void PrintDirM100(BTREE btree) {

	if (btree != NULL) {
		if (((DIR*)DATA(btree))->n_Kb > 100)
			printf("A Diretoria %s tem mais de 100 kb, tem %d", ((DIR*)DATA(btree))->nome, ((DIR*)DATA(btree))->n_Kb);
		PrintDirM100(LEFT(btree));
		PrintDirM100(RIGHT(btree));

	}
}


int CountTotalFiles(BTREE btree, char* directoryname)
{
	int cont = 0;

	if (btree != NULL) {
		if ((strcmp(((DIR*)DATA(btree))->nome, directoryname)))
			cont += ((DIR*)DATA(btree))->n_fich + CountTotalFiles(LEFT(btree), directoryname) + CountTotalFiles(RIGHT(btree), directoryname);

	}

	return cont;
}


int CountPrintEmptyDirs(BTREE btree)
{
	int cont = 0;
	if (btree != NULL) {
		if (((DIR*)DATA(btree))->n_Kb == 0) {
			cont += 1;
			printf("A diretoria %s está vazia", ((DIR*)DATA(btree))->nome);
		}

		CountPrintEmptyDirs(LEFT(btree));
		CountPrintEmptyDirs(RIGHT(btree));

	}

	printf("%d", cont);
	return cont;
}


BTREE_NODE* NewBtreeNode(void* data)
{
	BTREE_NODE* tmp_pt;
	if ((tmp_pt = (BTREE_NODE*)malloc(sizeof(BTREE_NODE))) != NULL) {
		DATA(tmp_pt) = data;
		LEFT(tmp_pt) = RIGHT(tmp_pt) = NULL;
	}
	return tmp_pt;
}

void BtreeFree(BTREE btree)
{
	if (btree != NULL) {
		BtreeFree(LEFT(btree));
		BtreeFree(RIGHT(btree));
		free(DATA(btree));
		free(btree);
	}
}







STATUS ReadFile(void** dirs, char* file_name)
{
	FILE* fp;   //pontiero po file
	int j, i = 0;//para iterar
	void* ptr_data;//guardar dados
	if ((fp = fopen(file_name, "r")) != NULL)//abrir leitura
	{
		while (!feof(fp))//enquanto nao chegar ao fim
		{
			if ((ptr_data = malloc(sizeof(DIR))) != NULL)//alocar memoria para um player
			{
				fscanf(fp, "%[^;];%d;%d\n", ((DIR*)ptr_data)->nome, &(((DIR*)ptr_data)->n_fich), &(((DIR*)ptr_data)->n_Kb));//ler ficheiro string até ;
			//	fscanf(fp, "%d\n", &(((PLAYER*)ptr_data)->sets));//até \n lê os sets
				dirs[i] = ptr_data;
				i++;
			}
			else //deu erro, apagr todos os que já estavam no vetor
			{
				for (j = i; j >= 0; j--)
					free(dirs[j]);
				return(ERROR);
			}
		}
		fclose(fp);
		return(OK);
	}
	else //erro na abertura
		return(ERROR);
}