#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAX_NAME 20
#define STAGES 15 //Eliminatórias


typedef struct _PLAYER
{
	char name[MAX_NAME];
	int sets;
}PLAYER;


typedef struct _BTREE_NODE
{
	void* data;
	struct _BTREE_NODE* left;
	struct _BTREE_NODE* right;
} BTREE_NODE;


typedef BTREE_NODE* BTREE;//ponteiro para um nó

typedef enum _BTREE_LOCATION { BTREE_LEFT, BTREE_RIGHT } BTREE_LOCATION;//Não usamos em principio
typedef enum _BOOLEAN { FALSE = 0, TRUE = 1 } BOOLEAN;
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
STATUS ReadPlayersFromFile(void**, char*);//para ler ficheiro
void PrintLeafs(BTREE);//Imprimir nós folhas
void BtreeFree(BTREE);//libertar memoria de uma arvore
void PrintWinnerGames(BTREE);//Vencedor de cada jogo
int CountTotalSets(BTREE);//Total de sets realizados
int CountWinnerSets(BTREE, void*);//Quantos sets o jogador que venceu o torneio ganhou
void PrintAllGames(BTREE);//Mostrar todos os jogos
void PrintGame(BTREE);
int CountLeafs(BTREE);
BTREE_NODE* MaisDireita(BTREE);
void RightLeaf(BTREE btree);

int main()
{
	BTREE Btree;
	void* players[STAGES];//vetor para guardar jogadores
	char file_name[MAX_NAME];//
	//printf("Nome do ficheiro: ");
	//scanf("%s", file_name);

	//if (ReadPlayersFromFile(players, file_name))
	if (ReadPlayersFromFile(players, "dep.txt"))//Booleano
	{
		Btree = CreateBtree(players, 0, STAGES);//Retorna ponteiro para nó com tamanho de vetor
		printf("\nLista dos %d participantes:\n", CountLeafs(Btree));
		PrintLeafs(Btree);
		printf("\nLista de Jogos:\n");
		PrintAllGames(Btree);
		printf("\nNumero de eliminatorias: %d", BtreeDeep(Btree) - 1);
		printf("\nNumero de Jogos: %d", BtreeSize(Btree) / 2);
		printf("\nNumero de Sets: %d", CountTotalSets(Btree));
		printf("\nVencedor do torneio: %s\n", ((PLAYER*)DATA(Btree))->name);
		printf("\nJogos disputados pelo Vencedor:\n");
		PrintWinnerGames(Btree);
		printf("\nSets ganhos pelo Vencedor: %d\n", CountWinnerSets(Btree, DATA(Btree)));
		printf("\nO jogador mais a direita e: %s ", ((PLAYER*)DATA(MaisDireita(Btree)))->name);
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
STATUS ReadPlayersFromFile(void** players, char* file_name)
{
	FILE* fp;   //pontiero po file
	int j, i = 0;//para iterar
	void* ptr_data;//guardar dados
	if ((fp = fopen(file_name, "r")) != NULL)//abrir leitura
	{
		while (!feof(fp))//enquanto nao chegar ao fim
		{
			if ((ptr_data = malloc(sizeof(PLAYER))) != NULL)//alocar memoria para um player
			{
				fscanf(fp, "%[^;];%d\n", ((PLAYER*)ptr_data)->name, &(((PLAYER*)ptr_data)->sets));//ler ficheiro string até ;
			//	fscanf(fp, "%d\n", &(((PLAYER*)ptr_data)->sets));//até \n lê os sets
				players[i] = ptr_data;
				i++;
			}
			else //deu erro, apagr todos os que já estavam no vetor
			{
				for (j = i; j >= 0; j--)
					free(players[j]);
				return(ERROR);
			}
		}
		fclose(fp);
		return(OK);
	}
	else //erro na abertura
		return(ERROR);
}
void PrintLeafs(BTREE btree)
{
	if (btree != NULL)
	{
		PrintLeafs(LEFT(btree));
		if (BtreeLeaf(btree))
			printf("\n%s\n", ((PLAYER*)DATA(btree))->name);
		PrintLeafs(RIGHT(btree));
	}
}

//Com dois exemplos
void PrintWinnerGames(BTREE btree)
{

	if (btree != NULL && !BtreeLeaf(btree))
	{
		PrintGame(btree);

		if (!strcmp(((PLAYER*)DATA(btree))->name, ((PLAYER*)DATA(LEFT(btree)))->name))
			PrintWinnerGames(LEFT(btree));
		else
			PrintWinnerGames(RIGHT(btree));

	//	if(((PLAYER*)DATA(btree))->sets > ((PLAYER*)DATA(LEFT(btree)))->sets)
		//	PrintWinnerGames(RIGHT(btree));
		//else
		//	PrintWinnerGames(LEFT(btree));
		
	}
	
}

int CountTotalSets(BTREE btree)
{
	int count = 0;

	if(btree != NULL)
	count = ((PLAYER*)DATA(btree))->sets + CountTotalSets(LEFT(btree)) + CountTotalSets(RIGHT(btree));
	return(count);
}

int CountWinnerSets(BTREE btree, void* winner)
{
	/*
	int count = 0;
	if (btree != NULL)
	{
		if (!strcmp(((PLAYER*)DATA(btree))->name, winner))
			count = ((PLAYER*)DATA(btree))->sets + CountWinnerSets(LEFT(btree), winner) + CountWinnerSets(RIGHT(btree), winner);
	}
	return (count);
	*/
	//Função do Stor
	
	int count = 0;
	if(btree != NULL){
	if(!strcmp(((PLAYER*)DATA(btree))->name, ((PLAYER*)winner)->name))
	count += ((PLAYER*)DATA(btree))->sets;
	count += CountWinnerSets(LEFT(btree), winner) + CountWinnerSets(RIGHT(btree), winner);
	}
	return (count);
	
}

void PrintAllGames(BTREE btree)
{
		if (btree != NULL && !BtreeLeaf(btree)) 
		{
			PrintAllGames(LEFT(btree));
			PrintGame(btree);
			PrintAllGames(RIGHT(btree));
		}
	
}

void PrintGame(BTREE btree)
{
	if (btree != NULL && LEFT(btree) != NULL && RIGHT(btree) != NULL)
		printf("%s (%d) vs (%d) %s \n", ((PLAYER*)DATA(LEFT(btree)))->name, ((PLAYER*)DATA(LEFT(btree)))->sets, ((PLAYER*)DATA(RIGHT(btree)))->sets, ((PLAYER*)DATA(RIGHT(btree)))->name);
}

int CountLeafs(BTREE btree) {
	int count = 0;
	if (btree != NULL)
	{
		if (BtreeLeaf(btree))
			count += 1;
		count+=CountLeafs(LEFT(btree)) + CountLeafs(RIGHT(btree));

	}
	return count;
}

void RightLeaf(BTREE btree)
{
	if (btree != NULL)
	{
		if (BtreeLeaf(btree))
			printf("\n%s\n", ((PLAYER*)DATA(btree))->name);
		RightLeaf(RIGHT(btree));
	}
}

BTREE_NODE* MaisDireita(BTREE btree)
{
	if (btree == NULL)
		return NULL;

	if (RIGHT(btree) != NULL)
	    return MaisDireita(RIGHT(btree));

	else
		return btree;
}