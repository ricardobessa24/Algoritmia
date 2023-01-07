#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef struct _BETREE_NODE {
	void* pData;
	struct _BTREE_NODE* pLeft;
	struct _BTREE_NODE* pRight;

}BTREE_NODE;

typedef BTREE_NODE* BTREE;

#define DATA(node) ((node)->pData)
#define LEFT(node) ((node)->pLeft)
#define RIGHT(node) ((node)->pRight)

#define EMPTY NULL
#define NO_LINK NULL

typedef enum _STATUS { ERROR = 0, OK = 1 }STATUS;
typedef enum { FALSE = 0, TRUE=1 }BOOLEAN;

//FUNÇÕES

STATUS initBTree(BTREE*);
BOOLEAN emptyBTree(BTREE);
BOOLEAN isLeaf(BTREE);
STATUS createNewBTNode(BTREE*, void*);
void printBTree(BTREE);
STATUS insertIntBST(BTREE*, void*);
int numNos(BTREE);
BTREE_NODE* searchBST(BTREE BT, int);
int findMax(BTREE);
int alturaBT(BTREE);
BTREE_NODE* InitNode(void*, BTREE_NODE*, BTREE_NODE*);
BTREE_NODE* CreateBT(void**, int, int);

void main()
{
	BTREE a;
	BTREE b;
	int* dados[10] = { 10,15,20,25,30,35,40,45,50,55 };

	initBTree(&a);
	printBTree(a);
	int x = 5;
	insertIntBST(&a, &x);
	int y = 1;
	insertIntBST(&a, &y);
	int z = 7;
	insertIntBST(&a, &z);
	printBTree(a);
	z = 0;
	printBTree(a);

	printf("\n\n numero de nos = %d", numNos(a));
	BTREE_NODE* find = searchBST(a, 7);
	if (find != NULL)
		printf("\n valor encontrado = %d", *(int*)DATA(find));
	else
		printf("\n valor nao encontrado");

	printf("\n O valor maximo = %d", findMax(a));
	printf("\n A altura da arvore e = %d", alturaBT(a));
	
	b = CreateBT(&dados, 1, 7);
	printBTree(b);

	printf("\n maximo = %d", findMax(b));
	printf("\n numero de nos = %d", numNos(b)); 
	printBTree(a);
}

//
STATUS initBTree(BTREE* pBT)
{
	*pBT = NULL;
	return OK;
}

BOOLEAN emptyBTree(BTREE BT)
{
	return(BT == NULL) ? TRUE : FALSE;

}

BOOLEAN isLeaf(BTREE BT)
{
	return (LEFT(BT) == NULL && RIGHT(BT) == NULL) ? TRUE : FALSE;
}

STATUS createNewBTNode(BTREE* pNew, void* pData)
{
	BTREE_NODE* pTemp;
	if((pTemp=(BTREE_NODE*)malloc(sizeof(BTREE_NODE))) == NULL);
	return ERROR;

	*pNew = pTemp;
	DATA(pTemp) = pData;
	LEFT(pTemp) = NULL;
	RIGHT(pTemp) = NULL;

	return OK;
}

void printBTree(BTREE BT)
{
	if (emptyBTree(BT) == TRUE) return;

	printBTree(LEFT(BT));
	printf("%d, ", *(int*)DATA(BT));
	printBTree(RIGHT(BT));
	return;
}

STATUS insertIntBST(BTREE* pBT, void* pData)
{
	if (emptyBTree(*pBT)) {
		BTREE_NODE* pNew;
		if (createNewBTNode(&pNew, pData) == ERROR)
			return ERROR;

		*pBT = pNew;
		return OK;
	}
	else {
		if (*(int*)(pData) < *(int*)(DATA(*pBT)))
			insertIntBST(&(LEFT(*pBT)), pData);
		else
			insertIntBST(&(RIGHT(*pBT)), pData);
	}

	return OK;
}

int numNos(BTREE BT)
{
	if (BT == NULL)
		return 0;
	
	
	 return 1 + numNos(LEFT(BT)) + numNos(RIGHT(BT));


}

// procurar um no na BST

BTREE_NODE* searchBST(BTREE BT, int x)
{
	if (BT == NULL || (int*)DATA(BT) == x)
		return BT;
	else
		if (x > *(int*)DATA(BT))
			return searchBST(RIGHT(BT), x);
		else
			return searchBST(LEFT(BT), x);
}

// ENCONTRAR VALOR MAXIMO DA ARVORE 
int findMax(BTREE BT)
{
	//caso base 
	if (BT == NULL)
		return INT_MIN;
	//retorna o máximo de 3 valores:
	//1) valor dp nó
	//2) valor do máximo da arvores da esquerda
	//3) valor maximo da arvore da direita

	int res = (int*)DATA(BT);
	int lres = findMax(LEFT(BT));
	int rres = findMax(RIGHT(BT));
	if (lres > res)
		res = lres;
	if (rres > res)
		res = rres;
	return res;

}
int alturaBT(BTREE BT)
{
	if (BT == NULL)
		return -1;
	else {
		int ae = alturaBT(LEFT(BT));
		int ad = alturaBT(RIGHT(BT));
		if (ae < ad)
			return ad + 1;
		else
			return ae + 1;
	}
}
BTREE_NODE* InitNode(void* pData, BTREE_NODE* nodel, BTREE_NODE* noder)
{
	BTREE_NODE* temp;
	temp = (BTREE_NODE*)malloc(sizeof(BTREE_NODE));
	DATA(temp) = pData;
	LEFT(temp) = nodel;
	RIGHT(temp) = noder;
	return temp;
}
BTREE_NODE* CreateBT(void**v, int i , int size)
{
	if (i >= size)
		return NULL;
	else
		return (InitNode((v + i), CreateBT(v, 2 * i + 1, size), CreateBT(v, 2 * i + 1, size)));

}