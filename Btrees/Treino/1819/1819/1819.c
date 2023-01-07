#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef enum _BOOLEAN { FALSE = 0, TRUE = 1 } BOOLEAN;
typedef struct _PERSON
{
	char name[50];
	int age;
	BOOLEAN alive;
} PERSON;

typedef struct _BTREE_NODE
{
	void* data;
	struct _BTREE_NODE* left;
	struct _BTREE_NODE* right;
} BTREE_NODE;


typedef BTREE_NODE* BTREE;//ponteiro para um nó

typedef enum _BTREE_LOCATION { BTREE_LEFT, BTREE_RIGHT } BTREE_LOCATION;//Não usamos em principio

typedef enum _STATUS { ERROR = 0, OK = 1 } STATUS;



#define DATA(node) ((node)->data)
#define LEFT(node) ((node)->left)
#define RIGHT(node) ((node)->right)
#define EMPTY NULL
#define NO_LINK NULL



BTREE_NODE* NewBtreeNode(void* data); //Novo nó
BTREE_NODE* AddBtreeNode(BTREE_NODE* upnode, BTREE_NODE* node, BTREE_LOCATION where);//Adicionar nó
int BtreeSize(BTREE btree); //Tamanho da arvore
int BtreeDeep(BTREE btree); //Altura da arvore
BOOLEAN BtreeLeaf(BTREE_NODE* node);//Se é folha ou não; Nó Folha -> são os nós de baixo porque não têm filhos
BTREE_NODE* InitNode(void*, BTREE_NODE*, BTREE_NODE*);// Inicia o nó esq ou dir
BTREE_NODE* CreateBtree(void**, int, int);//Criar arvore a partir de um vetor
STATUS ReadFile(void**, char*);//para ler ficheiro
void BtreeFree(BTREE);//libertar memoria de uma arvore
int CountPessoasVivas(BTREE Btree);
void ChangeName(BTREE btree, char* nome_inicial,char* nome_final);
BTREE_NODE* MaisDireita(BTREE btree);


int main()
{
	BTREE Btree;
	void* persons[15];//vetor para guardar jogadores
	char file_name[50];//
	char nome_inicial[30];
	char nome_final[30];
	//printf("Nome do ficheiro: ");
	//scanf("%s", file_name);

	//if (ReadPlayersFromFile(players, file_name))
	if (ReadFile(persons, "Pessoas.txt"))//Booleano
	{
		Btree = CreateBtree(persons, 0, 15);//Retorna ponteiro para nó com tamanho de vetor

		printf("Pessoas Vivas: %d \n", CountPessoasVivas(Btree));

		printf("Digite o nome que pretende mudar: \n");
		scanf("%s", nome_inicial);
		printf("Digite o novo nome: \n");
		scanf("%s", nome_final);
		ChangeName(Btree, nome_inicial, nome_final);

	//	Adicionaradireita()


		
		BtreeFree(Btree);
		system("pause");
	}
	else
		printf("ERRO na leitura do ficheiro\n");
	system("pause");
	return 0;
}

BTREE_NODE* NewBtreeNode(void* data)
{
	BTREE_NODE* tmp_pt;
	if ((tmp_pt = (BTREE_NODE*)malloc(sizeof(BTREE_NODE))) != NULL)
	{
		DATA(tmp_pt) = data;
		LEFT(tmp_pt) = RIGHT(tmp_pt) = NULL;
	}
	return tmp_pt;
}

BTREE_NODE* AddBtreeNode(BTREE_NODE* upnode, BTREE_NODE* node, BTREE_LOCATION where)
{
	BTREE_NODE* tmp_pt = upnode;
	if (where == BTREE_LEFT)
	{
		if (LEFT(upnode) == NULL)
			LEFT(upnode) = node;
		else
			tmp_pt = NULL;
	}
	else
	{
		if (RIGHT(upnode) == NULL)
			RIGHT(upnode) = node;
		else
			tmp_pt = NULL;
	}
	return tmp_pt;
}
BTREE_NODE* InitNode(void* ptr_data, BTREE_NODE* node1, BTREE_NODE* node2)
{
	BTREE_NODE* tmp_pt = NULL;
	tmp_pt = NewBtreeNode(ptr_data);
	LEFT(tmp_pt) = node1;
	RIGHT(tmp_pt) = node2;
	return(tmp_pt);
}
BTREE_NODE* CreateBtree(void** v, int i, int size)
{
	if (i >= size) //maior que o size
		return(NULL);
	else
		return(InitNode(*(v + i), CreateBtree(v, 2 * i + 1, size), CreateBtree(v, 2 * i + 2, size)));//Dados metidos na arvore, no na esquerda, no direita
}
void BtreeFree(BTREE btree)
{
	if (btree != NULL)
	{
		BtreeFree(LEFT(btree));
		BtreeFree(RIGHT(btree));
		free(btree);
	}
}
int BtreeSize(BTREE btree)
{
	int count = 0;
	if (btree != NULL)
		count = 1 + BtreeSize(LEFT(btree)) + BtreeSize(RIGHT(btree));
	return(count);
}
BOOLEAN BtreeLeaf(BTREE_NODE* btree)
{
	if ((LEFT(btree) == NULL) && (RIGHT(btree) == NULL))
		return(TRUE);
	else
		return(FALSE);
}

int BtreeDeep(BTREE btree)
{
	int deep = 0, left, right;
	if (btree != NULL)
	{
		left = BtreeDeep(LEFT(btree));
		right = BtreeDeep(RIGHT(btree));
		deep = 1 + ((left > right) ? left : right);
	}
	return(deep);
}

STATUS ReadFile(void** persons, char* file_name)
{
	FILE* fp;
	int aux, j, i = 0;
	void* ptr_data;
	if ((fp = fopen(file_name, "r")) != NULL) {
		while (!feof(fp)) {
			if ((ptr_data = malloc(sizeof(PERSON))) != NULL) {
				fscanf(fp, "%[^;];%d;%d\n", ((PERSON*)ptr_data)->name, &((PERSON*)ptr_data)->age, &aux);
				if (aux) ((PERSON*)ptr_data)->alive = TRUE;
				else ((PERSON*)ptr_data)->alive = FALSE;
				persons[i] = ptr_data;
				i++;
			}
			else {
				for (j = i; j >= 0; j--)
					free(persons[j]);
				return(ERROR);
			}
		}
		fclose(fp);
		return(OK);
	}
	else
		return(ERROR);
}


int CountPessoasVivas(BTREE Btree)
{
	int count = 0;
	if (Btree != NULL)
	{
		
		if (((PERSON*)DATA(Btree))->alive == TRUE)
			count += 1;
		count += CountPessoasVivas(LEFT(Btree)) + CountPessoasVivas(RIGHT(Btree));
	}

	return (count);
}

void ChangeName(BTREE btree, char* nome_inicial, char* nome_final)
{
	if (btree != NULL)
	{
		ChangeName(LEFT(btree),nome_inicial,nome_final);
		if (!(strcmp(((PERSON*)DATA(btree))->name, nome_inicial)))
		{
			strcpy(((PERSON*)DATA(btree))->name, nome_final);
		}
		ChangeName(RIGHT(btree), nome_inicial, nome_final);
	}

}


BTREE_NODE* MaisDireita(BTREE btree)
{
	if (btree == NULL)
		return NULL;
	if (RIGHT(btree) != NULL)
		return MaisDireita(RIGHT(btree));

	addPessoas(btree, ReadPessoa(), ReadPessoa());
}


BTREE_NODE* ReadPessoa() {
	char nome[20], OP = ' ';
	int idade = 0, vivo = 0;
	void* aux;
	// Lê os dados
	printf("\n#Nova Pessoa\n\n");
	printf("Nome: ");
	gets_s(nome, 20);
	printf("Idade: ");
	scanf("%d", &idade);
	printf("\n");
	do {
		printf("Vivo?\n[S][N]: ");
		scanf("%c", &OP);
	} while (OP != 'S' && OP != 'N' && OP != 's' & OP != 'n');
	// Tenta alocar o apontador para a data
	if ((aux = (PERSON*)malloc(sizeof(PERSON))) != NULL) {
		// Atribui os dados
		strcpy((((PERSON*)aux)->name), nome);
		(((PERSON*)aux)->age) = idade;
		if (OP == 'S' || OP == 's')
			(((PERSON*)aux)->alive) = TRUE;
		else
			(((PERSON*)aux)->alive) = FALSE;
	}
	// Retorna um nó criado com a data lida
	return NewBtreeNode(aux);
}
BOOLEAN addPessoas(BTREE_NODE* root, BTREE_NODE* left, BTREE_NODE* right) {
	// Se a raíz for nula, a árvore está vazia e é impossível adicionar nós filhos
	if (root == NULL)
		return FALSE;
	// Adicionamos caso o nó à direita do atual seja nulo, ou seja, se estivermos na folha mais à direita
	if (IsLeaf(root)) {
		RIGHT(root) = right;
		LEFT(root) = left;
		return TRUE;
	}

}