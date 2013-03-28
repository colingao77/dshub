#include "Graph.h"
#include <stdio.h>

Graph::Graph()
{
}

Graph::~Graph()
{
}

bool PrintGraphProc(Vertex* pVertex, void* lParam)
{
//	printf("%d ", pVertex->index);
	char c = 'A' + pVertex->index;
	printf("%c ", c);
	return true;
}
