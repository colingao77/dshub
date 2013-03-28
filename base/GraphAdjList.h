#ifndef __GRAPH_ADJ_LIST_H__
#define __GRAPH_ADJ_LIST_H__

#include "config.h"
#include "Graph.h"
#include <stdio.h>

typedef struct ArcNode
{
	Edge arcinfo;
	struct ArcNode *nextarc;
}ArcNode;

typedef struct VertexNode
{
	Vertex vertexinfo;
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

	bool Init(const char* filename, InitMode mode);
	bool InitByMatrix(FILE* stream);
	bool InitByEdges(FILE* stream);
	void Print(bool all = false);

	//traverse
	void DFSTraverse(GraphEnumProc pProc, void* lParam);
	void BFSTraverse(GraphEnumProc pProc, void* lParam);

	//Get the vertex information by vertex index
	virtual bool GetVertex(int vertex, Vertex* pVertexInfo);
	
	//Put the vertex into the graph
	virtual int PutVertex(const Vertex* pVertexInfo);
	
	//Find the first adjacent vertex index of the specified "vertex", return NULL if no such vertex
	virtual ArcNode* FirstAdjVertex(int vertex);
	
	//Find the next adjacent vertex index of the specified "vertex", relative to ArcNode "arc"
	//return NULL if no such vertex
	virtual ArcNode* NextAdjVertex(int vertex, ArcNode* arc);
	
	//Insert edge into the graph
	virtual bool InsertEdge(const Edge* pEdge);
	virtual bool InsertEdge(int from, int to, int cost);
	
	//Delete edge from the graph
	virtual bool DeleteEdge(int from, int to);

private:
	bool DFS(GraphEnumProc pProc, void* lParam, int v, bool* visited);
	void ReverseAdjList();
};

#endif