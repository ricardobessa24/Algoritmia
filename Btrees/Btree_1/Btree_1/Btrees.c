#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>


typedef struct _BTREE_NODE {
	void** pData; //ponteiro para os dados
	struct _BTREE_NODE* pLeft;
	struct _BTREE_NODE* pRight;
}BTREE_NODE;


typedef BTREE_NODE* BTREE;

#define DATA(node) ((node)->pData)
#define LEFT(node) ((node)->pLeft)
#define RIGHT(node) ((node)->pRight)

#define EMPTY NULL
#define NO_LINK NULL

typedef enum _STATUS { ERROR=0, OK=1}STATUS;
typedef enum {FALSE = 0, TRUE = 1}BOOLEAN;

//Fun��es
//---declaracao de funcoes----------
STATUS initBTree(BTREE*);
BOOLEAN emptyBTree(BTREE);
BOOLEAN isLeaf(BTREE_NODE*);
STATUS createNewBTNode(BTREE*, void*);
void printIntBTree(BTREE);
STATUS insertIntBST(BTREE*, void*);
STATUS insertBT(BTREE*, void*, void*, void*);
//-------------------------------------------





//
void main() {
	BTREE a;


	initBTree(&a);
	printIntBTree(a);

	int x = 5;
	insertIntBST(&a, &x);
	int y = 1;
	insertIntBST(&a, &y);
	printIntBTree(a);
	printf("\n\n");
	int z = 7;
	insertIntBST(&a, &z);
	printIntBTree(a);















}













//

/**************************************************************
* Fun��o initBTree(): Inicializa a �rvore bin�ria
*
* Par�metros: pBT � �rvore bin�ria (passado por ref)
* Sa�da: STATUS
***************************************************************/
STATUS initBTree(BTREE* pBT)
{
	*pBT = NULL;
	return OK;
}



/**************************************************************
* Fun��o emptyBTree(): verifica se a �rvore bin�ria est� vazia
*
* Par�metros: BT � �rvore bin�ria
* Sa�da: TRUE se a �rvore bin�ria estiver vazia, FALSE caso contr�rio
***************************************************************/
BOOLEAN emptyBTree(BTREE BT)
{
	return (BT == NULL) ? TRUE : FALSE;
}


/**************************************************************
* Fun��o isLeaf(): verifica se adeterminado n� da �rvore bin�ria � folha
*
* Par�metros: pNode � apontador para n� (da �rvore bin�ria)
* Sa�da: TRUE se for uma folha, FALSE caso contr�rio
***************************************************************/
BOOLEAN isLeaf(BTREE_NODE* pNode)
{
	return ((LEFT(pNode) == NULL) && (RIGHT(pNode) == NULL)) ? TRUE : FALSE;
}

/**************************************************************
* Fun��o printBTree(): apresenta no ecr� os elementos da �rvore bin�ria
*
* Par�metros: BT � �rvore bin�ria
* Sa�da: void
*
* Esta fun��o n�o � gen�rica: s� funciona para elementos de tipo INT
***************************************************************/
void printIntBTree(BTREE BT)
{
	if (emptyBTree(BT) == TRUE) return;
	printIntBTree(LEFT(BT));
	printf("%d, ", *(int*)DATA(BT));
	printIntBTree(RIGHT(BT));
	return;
}

/**************************************************************
* Fun��o insertIntBST(): insere um elemento (n�) numa BST
*
* Par�metros: pBT � BST (passado por ref)
* pData - apontador gen�rico para os dados a inserir no n� criado
* Sa�da: OK se o n� foi inserido na BST e ERROR caso contr�rio
* Esta fun��o n�o � gen�rica: s� funciona para elementos de tipo INT
***************************************************************/
STATUS insertIntBST(BTREE* pBT, void* pData)
{
	if (emptyBTree(*pBT))
	{
		BTREE_NODE* pNew;
		if (createNewBTNode(&pNew, pData) == ERROR)
			return ERROR;
		*pBT = pNew;
		return OK;
	}
	else if (*(int*)(pData) < *(int*)(DATA(*pBT)))
		insertIntBST(&(LEFT(*pBT)), pData);
	else insertIntBST(&(RIGHT(*pBT)), pData);
	return OK;
}



/**************************************************************
* Fun��o createNewBTNode(): cria um n� da �rvore bin�ria
*
* Par�metros: pData - apontador gen�rico para os dados a inserir no n� criado
* Sa�da: apontador para o n� criado ou NULL em caso de erro
***************************************************************/


STATUS createNewBTNode(BTREE_NODE * *pNew, void* pData)
{
		BTREE_NODE* pTemp;
		if ((pTemp = (BTREE_NODE*)malloc(sizeof(BTREE_NODE))) == NULL)
			return ERROR;
		*pNew = pTemp;
		DATA(pTemp) = pData;
		LEFT(pTemp) = NULL;
		RIGHT(pTemp) = NULL;
		return OK;
}