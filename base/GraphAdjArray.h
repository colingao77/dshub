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
	Vertex		vexs[MAX_VERTEX_NUM];
	Edge		arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
public:
	GraphAdjArray();
	virtual ~GraphAdjArray();

	bool Init(const char* filename, InitMode mode);
	void Print();

	bool InitByMatrix(FILE* stream);
	bool InitByEdges(FILE* stream);
	

	//traverse
	void DFSTraverse(GraphEnumProc pProc, void* lParam);
	void BFSTraverse(GraphEnumProc pProc, void* lParam);


	//Get the vertex information by vertex index
	virtual bool GetVertex(int vertex, Vertex* pVertexInfo);
	
	//Put the vertex into the graph
	virtual int PutVertex(const Vertex* pVertexInfo);
	
	//Find the first adjacent vertex index of the specified "vertex", -1 if no such vertex
	virtual int FirstAdjVertex(int vertex);
	
	//Find the next adjacent vertex index of the specified "vertex", relative to vertex "w"
	//-1 if no such vertex
	virtual int NextAdjVertex(int vertex, int w);
	
	//Insert edge into the graph
	virtual bool InsertEdge(const Edge* pEdge);
	virtual bool InsertEdge(int from, int to, int cost);
	
	//Delete edge from the graph
	virtual bool DeleteEdge(int from, int to);

private:
	
	bool DFS(GraphEnumProc pProc, void* lParam, int vertex, bool* visited);
};

#endif