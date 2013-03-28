#include "GraphAdjList.h"
#include <string.h>
#include <queue>

GraphAdjList::GraphAdjList() : kind(UDG), vexnum(0), arcnum(0)
{
	memset(vexs, 0, sizeof(vexs));
}
GraphAdjList::~GraphAdjList()
{
	ArcNode *pArc, *pTemp;
	for(int i = 0; i < vexnum; i++)
	{
		pArc = vexs[i].firstarc;
		while(pArc != NULL)
		{
			pTemp = pArc;
			pArc = pArc->nextarc;

			delete pTemp;
		}
	}
}

bool GraphAdjList::Init(const char* filename, InitMode mode)
{
	bool ret = false;
	
	FILE* input = NULL;
	do 
	{
		input = fopen(filename, "rb");
		if(input == NULL)
		{
			break;
		}
		
		if(mode == MATRIX)
		{
			ret = InitByMatrix(input);
		}
		else if(mode == EDGE)
		{
			ret = InitByEdges(input);
		}
	} while (false);
	
	if(input)
	{
		fclose(input);
	}
	return ret;
}

bool GraphAdjList::InitByMatrix(FILE* stream)
{
	if(stream == NULL)
	{
		printf("null input stream\n");
		return false;
	}
	
	int ret, m, i, j, cost;
	char c;
	ret = fscanf(stream, "%d%c", &m, &c);
	if(ret != 2)
	{
		printf("invalid format: vertex num invalid\n");
		return false;
	}
	
	Vertex vertex;
	for(i = 0; i < m; i++)
	{
		vertex.index = i;
		PutVertex(&vertex);

		for(j = 0; j < m; j++)
		{
			ret = fscanf(stream, "%d", &cost);
			if(ret != 1)
			{
				printf("invalid format: cell(%d, %d) invalid\n");
				return false;
			}
			ret = fscanf(stream, "%c", &c);
			if(ret != 1)
			{
				printf("invalid format: no trailing char after cell(%d, %d)\n", i, j);
				return false;
			}
			
			if(cost == 0)
			{
				continue;
			}

			InsertEdge(i, j, cost);
		}
	}
	
	vexnum = m;

	//optional: reverse the list to make sure the adjacent list has the same order with input data
	ReverseAdjList();
	
	return true;
}
bool GraphAdjList::InitByEdges(FILE* stream)
{
	if(stream == NULL)
	{
		printf("null input stream\n");
		return false;
	}
	
	int i, m, n, ret;
	int x, y, cost;
	char c;
	
	ret = fscanf(stream, "%d %d", &m, &n);
	if(ret != 2)
	{
		printf("invalid format: vertex num or edge num invalid\n");
		return false;
	}
	fscanf(stream, "%c", &c);
	
	Vertex vertex;
	for(i = 0; i < m; i++)
	{
		vertex.index = i;
		PutVertex(&vertex);
	}

	for(i = 0; i < n; i++)
	{
		ret = fscanf(stream, "%d %d %d", &x, &y, &cost);
		if(ret != 3)
		{
			printf("invalid format: %d edge invalid\n", i);
			return false;
		}
		fscanf(stream, "%c", &c);

		InsertEdge(x, y, cost);
		InsertEdge(y, x, cost);
	}

	//optional: reverse the list to make sure the adjacent list has the same order with input data
	ReverseAdjList();
	
	return true;
}
void GraphAdjList::Print(bool all)
{
	if(vexnum <= 0)
	{
		printf("[Empty graph]\n");
		return;
	}

	if(all)
	{
		printf("%2d %2d\n", vexnum, arcnum);
	}
	else
	{
		printf("%2d %2d\n", vexnum, arcnum/2);
	}
	for(int i = 0; i < vexnum; i++)
	{
		ArcNode* pArc = vexs[i].firstarc;
		while(pArc != NULL)
		{
			if((vexs[i].vertexinfo.index <= pArc->arcinfo.to) || all)
			{
				printf("%2d %2d %2d\n", vexs[i].vertexinfo.index, pArc->arcinfo.to, pArc->arcinfo.cost);
			}
			
			pArc = pArc->nextarc;
		}
	}
}

//Get the vertex information by vertex index
bool GraphAdjList::GetVertex(int vertex, Vertex* pVertexInfo)
{
	if(vertex < 0 || vertex >= vexnum)
	{
		return false;
	}
	*pVertexInfo = vexs[vertex].vertexinfo;
	return true;
}

//Put the vertex into the graph
int GraphAdjList::PutVertex(const Vertex* pVertexInfo)
{
	vexs[vexnum].vertexinfo = *pVertexInfo;
	vexs[vexnum].firstarc = NULL;
	vexnum++;

	return pVertexInfo->index;
}

//Find the first adjacent vertex index of the specified "vertex", return NULL if no such vertex
ArcNode* GraphAdjList::FirstAdjVertex(int vertex)
{
	return vexs[vertex].firstarc;
}

//Find the next adjacent vertex index of the specified "vertex", relative to ArcNode "arc"
//return NULL if no such vertex
ArcNode* GraphAdjList::NextAdjVertex(int vertex, ArcNode* arc)
{
	//validation TODO
	return arc->nextarc;
}

//Insert edge into the graph
bool GraphAdjList::InsertEdge(const Edge* pEdge)
{
	//create new ArcNode
	ArcNode* pArcNode = new ArcNode();
	pArcNode->arcinfo = *pEdge;

	//point to the adjacent arc list head
	pArcNode->nextarc = vexs[pEdge->from].firstarc;

	//update head with the new Arc
	vexs[pEdge->from].firstarc = pArcNode;

	arcnum++;
	
	return true;
}
bool GraphAdjList::InsertEdge(int from, int to, int cost)
{
	Edge edge;
	edge.from = from;
	edge.to = to;
	edge.cost = cost;

	return InsertEdge(&edge);
}

//Delete edge from the graph
bool GraphAdjList::DeleteEdge(int from, int to)
{
	if(from < 0 || from >= vexnum)
	{
		return false;
	}

	ArcNode** pArc = &(vexs[from].firstarc);
	ArcNode* pEntry;
	while(*pArc != NULL)
	{
		pEntry = *pArc;

		//delete it
		if(pEntry->arcinfo.to == to)
		{
			*pArc = pEntry->nextarc;

			delete pEntry;

			return true;
		}
		else
		{
			pArc = &pEntry->nextarc;
		}
	}
	return false;
}

void GraphAdjList::ReverseAdjList()
{
	ArcNode *prev, *curr, *next;
	for(int i = 0; i < vexnum; i++)
	{
		prev = NULL;
		curr = vexs[i].firstarc;
		while(curr)
		{
			next = curr->nextarc;
			curr->nextarc = prev;
			prev = curr;
			curr = next;
		}
		vexs[i].firstarc = prev;
	}
}

//traverse
void GraphAdjList::DFSTraverse(GraphEnumProc pProc, void* lParam)
{
	if(vexnum <= 0)
	{
		return;
	}

	bool* visited = new bool[vexnum];
	memset(visited, 0, sizeof(bool) * vexnum);

	for(int v = 0; v < vexnum; v++)
	{
		if(!visited[v])
		{
			if(!DFS(pProc, lParam, v, visited))
			{
				return;
			}
		}
	}

	delete visited;
}

bool GraphAdjList::DFS(GraphEnumProc pProc, void* lParam, int v, bool* visited)
{
	//visit vertex v now
	visited[v] = true;
	if(!pProc(&vexs[v].vertexinfo, lParam))
	{
		return false;
	}

	for(ArcNode* pArc = FirstAdjVertex(v); pArc != NULL; pArc = NextAdjVertex(v, pArc))
	{
		if(!visited[pArc->arcinfo.to])
		{
			if(!DFS(pProc, lParam, pArc->arcinfo.to, visited))
			{
				return false;
			}
		}
	}
	return true;
}

void GraphAdjList::BFSTraverse(GraphEnumProc pProc, void* lParam)
{
	if(vexnum <= 0)
	{
		return;
	}
	
	bool* visited = new bool[vexnum];
	memset(visited, 0, sizeof(bool) * vexnum);
	
	std::queue<int> que;
	int u, w;
	for(int v = 0; v < vexnum; v++)
	{
		if(visited[v])
		{
			continue;
		}

		//visit before enqueueing
		visited[v] = true;
		if(!pProc(&vexs[v].vertexinfo, lParam))
		{
			return;
		}
		que.push(v);
	
		while(!que.empty())
		{
			u = que.front();
			que.pop();

			for(ArcNode* pArc = FirstAdjVertex(u); pArc != NULL; pArc = NextAdjVertex(u, pArc))
			{
				w = pArc->arcinfo.to;
				if(visited[w])
				{
					continue;
				}

				visited[w] = true;
				if(!pProc(&vexs[w].vertexinfo, lParam))
				{
					return;
				}
				que.push(w);
			}
		}
	}
	
	delete visited;
}