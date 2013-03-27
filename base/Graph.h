#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "config.h"

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

#define MAX_VERTEX_NUM 100
#define VERTEX_NAME_BUF	16

typedef struct VetexType
{
	int index;
}VetexType;

typedef struct ArcType
{
	int cost;
	//other informations...
}ArcType;

//return false to stop enumeration, else continue
typedef bool (*GraphEnumProc)(int vertex, void* lParam);

bool PrintGraphProc(int vertex, void* lParam);

class Graph
{
public:
	Graph();
	virtual ~Graph();
};

#endif