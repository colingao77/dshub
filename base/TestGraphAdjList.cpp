#include "test.h"
#include "GraphAdjList.h"
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

void TestGraphAdjList()
{
	if(TEST_GRAPH_ADJ_List == 0)
	{
		return;
	}

	for(int i = 0; i < COUNT_OF(params); i++)
	{
		GraphAdjList graph1;
		graph1.Init(params[i].filename, params[i].mode);

		printf("Initialized by %s\n", ((params[i].mode == MATRIX) ? "MATRIX" : "EDGE"));
		graph1.Print();

		printf("DFS: ");
		graph1.DFSTraverse(PrintGraphProc, NULL);
		printf("\n");

		printf("BFS: ");
		graph1.BFSTraverse(PrintGraphProc, NULL);
		printf("\n");
	}
	
	PrintSep(__FILE__);
}