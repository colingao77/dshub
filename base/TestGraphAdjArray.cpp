#include "test.h"
#include "GraphAdjArray.h"
#include "Utils.h"
#include <string.h>
#include <stdio.h>

static bool InitGraph(GraphAdjArray* pGraph, const char* name, int initMode)
{
	bool ret = false;
	
	FILE* input = NULL;
	do 
	{
		input = fopen(name, "rb");
		if(input == NULL)
		{
			break;
		}
		
		if(initMode == MATRIX)
		{
			ret = pGraph->InitByMatrix(input);
		}
		else if(initMode == EDGE)
		{
			ret = pGraph->InitByEdges(input);
		}
	} while (false);
	
	if(input)
	{
		fclose(input);
	}
	return ret;
}

void TestGraphAdjArray()
{
	if(TEST_GRAPH_ADJ_ARRAY == 0)
	{
		return;
	}
	FILE *input = NULL;

	GraphAdjArray graph1;
	InitGraph(&graph1, "./data/matrix1.in", MATRIX);
	graph1.Print();
	graph1.DFS(PrintGraphProc, NULL);
	printf("\n");

	GraphAdjArray graph2;
	InitGraph(&graph2, "./data/edge1.in", EDGE);
	graph2.Print();
	graph2.BFS(PrintGraphProc, NULL);
	printf("\n");

	PrintSep(__FILE__);
}