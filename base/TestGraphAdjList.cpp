#include "test.h"
#include "GraphAdjList.h"
#include "Utils.h"
#include <string.h>
#include <stdio.h>

static bool InitGraph(GraphAdjList* pGraph, const char* name, int initMode)
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

void TestGraphAdjList()
{
	if(TEST_GRAPH_ADJ_List == 0)
	{
		return;
	}

	GraphAdjList graph1;
	InitGraph(&graph1, "./data/matrix1.in", MATRIX);
	graph1.Print();

	GraphAdjList graph2;
	InitGraph(&graph2, "./data/edge1.in", EDGE);
	graph2.Print(true);
	
	PrintSep(__FILE__);
}