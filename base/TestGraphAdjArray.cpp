#include "test.h"
#include "GraphAdjArray.h"
#include "Utils.h"
#include <string.h>
#include <stdio.h>

typedef struct InitParam
{
	const char* filename;
	InitMode mode;
}InitParam;

static InitParam params[] = 
{
	{"./data/matrix1.in", MATRIX},
	{"./data/edge1.in", EDGE},

	{"./data/matrix2.in", MATRIX},
	{"./data/edge2.in", EDGE}
};

static bool PrintEnumProc(TreeNode* pNode, void* lParam)
{
	Vertex* pVertex = (Vertex*)pNode->GetData();
	printf("%c ", 'A' + pVertex->index);
	return true;
}

void TestGraphAdjArray()
{
	if(TEST_GRAPH_ADJ_ARRAY == 0)
	{
		return;
	}

	CSTreeNode root;
	Vertex rootVertex;
	rootVertex.index = 25;
	root.data = &rootVertex;
	CSTreeNode *pForest = NULL, *pRoot = &root;

	for(int i = 0; i < COUNT_OF(params); i++)
	{
		GraphAdjArray graph1;
		graph1.Init(params[i].filename, params[i].mode);
		
		printf("Initialized by %s\n", ((params[i].mode == MATRIX) ? "MATRIX" : "EDGE"));
		graph1.Print();

		printf("DFS: ");
		graph1.DFSTraverse(PrintGraphProc, NULL);
		printf("\n");

		printf("BFS: ");
		graph1.BFSTraverse(PrintGraphProc, NULL);
		printf("\n");

		pForest = NULL;
		graph1.DFSForest(&pForest);
		pRoot->firstchild = pForest;

		printf("PreOrder visit the DFSForest: ");
		pRoot->PreOrderEnum(PrintEnumProc, NULL);
		printf("\n");

		printf("PostOrder visit the DFSForest: ");
		pRoot->PostOrderEnum(PrintEnumProc, NULL);
		printf("\n");

		printf("BFS visit the DFSForest: ");
		pRoot->BFSEnum(PrintEnumProc, NULL);
		printf("\n");
	}

	PrintSep(__FILE__);
}