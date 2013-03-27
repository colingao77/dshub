#include "test.h"
#include "CSTreeNode.h"
#include "Utils.h"
#include <string.h>
#include <stdio.h>

#define MAX_NODE_COUNT 100
#define MAX_CHILD_COUNT 10

static PCSTreeNode table[MAX_NODE_COUNT];

static CSTreeNode* CreateCSTree(int a[][MAX_CHILD_COUNT], int n)
{
	if(n <= 0)
	{
		return NULL;
	}

	memset(table, 0, sizeof(table));

	//1. generate TreeNode
	int i, j;
	for(i = 0; i < n; i++)
	{
		if(table[i] == NULL)
		{
			table[i] = new CSTreeNode((void*)i);
		}

		for(j = 0; j < MAX_CHILD_COUNT && a[i][j] >= 0; j++)
		{
			if(table[a[i][j]] == NULL)
			{
				table[a[i][j]] = new CSTreeNode((void*)a[i][j]);
			}
		}
	}

	//2. build relationships in TreeNodes
	PCSTreeNode pParent = NULL, pNode = NULL, pChild = NULL;
	for(i = 0; i < n; i++)
	{
		pParent = pNode = table[i];		
		for(j = 0; j < MAX_CHILD_COUNT && a[i][j] >= 0; j++)
		{
			pChild = table[a[i][j]];
			pChild->parent = pParent;
			if(j == 0)
			{
				pNode->firstchild = pChild;
			}
			else
			{
				pNode->nextsibling = pChild;
			}
			pNode = pChild;
		}
	}

	return table[0];
}

static bool PrintEnumProc(TreeNode* pNode, void* lParam)
{
	int val = (int)pNode->GetData();
	CSTreeNode* pParent = ((CSTreeNode*)pNode)->parent;
	printf("%d(p=%d) ", val, ((pParent == NULL) ? -1 : (int)pParent->GetData()));
	return true;
}

void TestCSTreeNode()
{
	if(TEST_CS_TREE_NODE == 0)
	{
		return;
	}
	
	//Create Tree
	int a[][MAX_CHILD_COUNT] = 
	{
		{1, 2, 3, -1}, //0
		{4, 5, 6, -1}, //1
		{7, 8, 9, -1}, //2
		{10, 11, 12, -1}, //3
	};
	CSTreeNode* pRoot = CreateCSTree(a, 4);

	//print tree in pre-order
	pRoot->PreOrderEnum(PrintEnumProc, NULL);
	printf("\n");

	//print tree in post-order
	pRoot->PostOrderEnum(PrintEnumProc, NULL);
	printf("\n");

	//print tree in bfs-order
	pRoot->BFSEnum(PrintEnumProc, NULL);
	printf("\n");
	
	//Destroy Tree
	DestoryTreeNode(pRoot, NULL);

	PrintSep(__FILE__);
}