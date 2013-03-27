#ifndef __GRAPH_ADJ_ARRAY_H__
#define __GRAPH_ADJ_ARRAY_H__

#include "config.h"
#include "Graph.h"
#include <stdio.h>

class GraphAdjArray
{
public:
	GraphKind	kind;
	int			vexnum;
	int			arcnum;
	VetexType	vexs[MAX_VERTEX_NUM];
	ArcType		arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
public:
	GraphAdjArray();
	virtual ~GraphAdjArray();

	bool InitByMatrix(FILE* stream);
	bool InitByEdges(FILE* stream);
	void Print();

	//traverse
	void DFS(GraphEnumProc pProc, void* lParam);
	void BFS(GraphEnumProc pProc, void* lParam);

private:
	
	bool DFS(GraphEnumProc pProc, void* lParam, int vertex, bool* visited);
};

#endif