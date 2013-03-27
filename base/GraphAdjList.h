#ifndef __GRAPH_ADJ_LIST_H__
#define __GRAPH_ADJ_LIST_H__

#include "config.h"
#include "Graph.h"
#include <stdio.h>

typedef struct ArcNode
{
	int adjvex;
	ArcType arcinfo;
	struct ArcNode *nextarc;
}ArcNode;

typedef struct VertexNode
{
	int vertex;
	ArcNode *firstarc;
}VertexNode;

class GraphAdjList
{
public:
	GraphKind	kind;
	int			vexnum;
	int			arcnum;
	VertexNode	vexs[MAX_VERTEX_NUM];
public:
	GraphAdjList();
	virtual ~GraphAdjList();

	bool InitByMatrix(FILE* stream);
	bool InitByEdges(FILE* stream);
	void Print(bool all = false);

	void InsertArc(int from, int to, int cost);
};

#endif