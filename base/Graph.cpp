#include "Graph.h"
#include <stdio.h>

Graph::Graph()
{
}

Graph::~Graph()
{
}

bool PrintGraphProc(int vertex, void* lParam)
{
	printf("%d ", vertex);
	return true;
}
