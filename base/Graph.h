#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "config.h"
#include <string.h>

#define MAX_VERTEX_NUM 100
#define VERTEX_NAME_BUF	16

enum GraphKind
{
	UDG,	//Undirected Graph
	DG,		//Digraph
	UDN,	//Undirected Network
	DN,		//Directed Network
};

enum InitMode
{
	MATRIX,
	EDGE
};

//Graph Vertex information structure
class Vertex
{
public:
	int index;	/* the vertex index. In real practice, this might be ID. We use the index here for simple. */

	//other meta informations
	char name[VERTEX_NAME_BUF];
public:
	Vertex() : index(-1)
	{
		memset(name, 0, sizeof(char) * VERTEX_NAME_BUF);
	}
};

//Graph Edge information structure
class Edge
{
public:
	int from;	/* "from" Vertex index, the "index" field in Vertex */
	int to;		/* "to" Vertex index */
	int cost;	/* the cost of this edge */

	//add other informations if needed
public:
	Edge() : from(-1), to(-1), cost(0) {}
};

//return false to stop enumeration, else continue
typedef bool (*GraphEnumProc)(Vertex* pVertex, void* lParam);

bool PrintGraphProc(Vertex* pVertex, void* lParam);

class Graph
{
public:
	Graph();
	virtual ~Graph();

	//Get the vertex information by vertex index
	virtual bool GetVertex(int vertex, Vertex* pVertexInfo) = 0;

	//Put the vertex into the graph
	virtual int PutVertex(const Vertex* pVertexInfo) = 0;

	//Find the first adjacent vertex index of the specified "vertex", -1 if no such vertex
	virtual int FirstAdjVertex(int vertex) = 0;

	//Find the next adjacent vertex index of the specified "vertex", relative to vertex "w"
	//-1 if no such vertex
	virtual int NextAdjVertex(int vertex, int w) = 0;

	//Insert edge into the graph
	virtual bool InsertEdge(const Edge* pEdge) = 0;

	//Delete edge from the graph
	virtual bool DeleteEdge(int from, int to) = 0;

	//Traverse the graph by the DFS order
	virtual bool DFSTraverse(GraphEnumProc pProc, void* lParam) = 0;

	//Traverse the graph by the BFS order
	virtual bool BFSTraverse(GraphEnumProc pProc, void* lParam) = 0;
};

#endif