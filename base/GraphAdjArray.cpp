#include "GraphAdjArray.h"
#include <string.h>
#include <queue>
#include <assert.h>

GraphAdjArray::GraphAdjArray() : kind(UDG), vexnum(0), arcnum(0)
{
	memset(vexs, 0, sizeof(vexs));
	memset(arcs, 0, sizeof(arcs));
}

GraphAdjArray::~GraphAdjArray()
{

}

bool GraphAdjArray::Init(const char* filename, InitMode mode)
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

bool GraphAdjArray::InitByMatrix(FILE* stream)
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
			
			//insert one edge
			InsertEdge(i, j, cost);

			ret = fscanf(stream, "%c", &c);
			if(ret != 1)
			{
				printf("invalid format: no trailing char after cell(%d, %d)\n", i, j);
				return false;
			}
		}
	}

	vexnum = m;

	return true;
}

bool GraphAdjArray::InitByEdges(FILE* stream)
{
	if(stream == NULL)
	{
		printf("null input stream\n");
		return false;
	}
	
	int i, j, m, n, ret;
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

	memset(arcs, 0, sizeof(arcs));

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

	//set the cost to infinity when the graph is network
	if(kind == UDN || kind == DN)
	{
		for(i = 0; i < m; i++)
		{
			for(j = 0; j < m; j++)
			{
				if(arcs[i][j].cost == 0)
				{
					arcs[i][j].cost = INFINITY;
				}
			}
		}
	}
	
	vexnum = m;
	arcnum = n * 2;
	
	return true;
}

void GraphAdjArray::Print()
{
	if(vexnum <= 0)
	{
		printf("[Empty graph]\n");
		return;
	}

	printf("%2d\n", vexnum);
	
	int i, j;
	for(i = 0; i < vexnum; i++)
	{
		for(j = 0; j < vexnum; j++)
		{
			if(arcs[i][j].cost == INFINITY)
			{
				printf("%2d ", 0);
			}
			else
			{
				printf("%2d ", arcs[i][j].cost);
			}
		}
		printf("\n");
	}
}

void GraphAdjArray::DFSTraverse(GraphEnumProc pProc, void* lParam)
{
	if(vexnum <= 0)
	{
		return;
	}
	bool* visited = new bool[vexnum];
	memset(visited, 0, sizeof(bool) * vexnum);

	for(int i = 0; i < vexnum; i++)
	{
		if(visited[i])
		{
			continue;
		}
		if(!DFS(pProc, lParam, i, visited))
		{
			return;
		}
	}

	delete [] visited;
}

bool GraphAdjArray::DFS(GraphEnumProc pProc, void* lParam, int vertex, bool* visited)
{
	visited[vertex] = true;
	if(!pProc(&vexs[vertex], lParam))
	{
		return false;
	}

	int w;
	for(w = FirstAdjVertex(vertex); w >= 0; w = NextAdjVertex(vertex, w))
	{
		if(!visited[w])
		{
			if(!DFS(pProc, lParam, w, visited))
			{
				return false;
			}
		}
	}
	return true;
}

void GraphAdjArray::BFSTraverse(GraphEnumProc pProc, void* lParam)
{
	if(vexnum <= 0)
	{
		return;
	}
	bool* visited = new bool[vexnum];
	memset(visited, 0, sizeof(bool) * vexnum);
	
	std::queue<int> que;
	
	int v, u, w;
	for(v = 0; v < vexnum; v++)
	{
		if(visited[v])
		{
			continue;
		}

		//visit before the vertex is enqueued
		visited[v] = true;
		if(!pProc(&vexs[v], lParam))
		{
			return;
		}
		//enqueue
		que.push(v);


		while(!que.empty())
		{
			//the vertex must be visited already
			u = que.front();
			que.pop();

			//push all the adjacent vertices of "u" to the queue
			for(w = FirstAdjVertex(u); w >= 0; w = NextAdjVertex(u, w))
			{
				if(!visited[w])
				{
					//visit before the vertex is enqueued
					visited[w] = true;
					if(!pProc(&vexs[w], lParam))
					{
						return;
					}
					//enqueue
					que.push(w);
				}
			}
		}
	}

	delete visited;
}

//Get the vertex information by vertex index
bool GraphAdjArray::GetVertex(int vertex, Vertex* pVertexInfo)
{
	if(vertex < 0 || vertex >= vexnum)
	{
		return false;
	}
	*pVertexInfo = vexs[vertex];
	return true;
}

//Put the vertex into the graph
int GraphAdjArray::PutVertex(const Vertex* pVertexInfo)
{
	vexs[vexnum] = *pVertexInfo;
	vexnum++;
	return pVertexInfo->index;
}

//Find the first adjacent vertex index of the specified "vertex", -1 if no such vertex
int GraphAdjArray::FirstAdjVertex(int vertex)
{
	if(vertex < 0 || vertex >= vexnum)
	{
		return -1;
	}
	for(int i = 0; i < vexnum; i++)
	{
		if(arcs[vertex][i].cost != 0)
		{
			return i;
		}
	}
	return -1;
}

//Find the next adjacent vertex index of the specified "vertex", relative to vertex "w"
//-1 if no such vertex
int GraphAdjArray::NextAdjVertex(int vertex, int w)
{
	if(vertex < 0 || vertex >= vexnum)
	{
		return -1;
	}
	for(int i = w + 1; i < vexnum; i++)
	{
		if(arcs[vertex][i].cost != 0)
		{
			return i;
		}
	}
	return -1;
}

//Insert edge into the graph
bool GraphAdjArray::InsertEdge(const Edge* pEdge)
{
	arcs[pEdge->from][pEdge->to] = *pEdge;
	return true;
}

bool GraphAdjArray::InsertEdge(int from, int to, int cost)
{
	arcs[from][to].from = from;
	arcs[from][to].to = to;
	arcs[from][to].cost = cost;
	return true;
}

//Delete edge from the graph
bool GraphAdjArray::DeleteEdge(int from, int to)
{
	arcs[from][to].cost = 0;
	return true;
}

void GraphAdjArray::DFSForest(PCSTreeNode* t)
{
	if(vexnum <= 0)
	{
		return;
	}

	bool* visited = new bool[vexnum];
	memset(visited, 0, sizeof(bool) * vexnum);

	CSTreeNode *p = NULL, *q = NULL;
	for(int v = 0; v < vexnum; v++)
	{
		if(visited[v])
		{
			continue;
		}

		p = new CSTreeNode(&vexs[v]);
		if(*t == NULL)
		{
			*t = p;
		}
		else
		{
			assert(q != NULL);
			q->nextsibling = p;
		}
		q = p;

		DFSTree(v, p, visited);
	}

	delete []visited;
}

//Traverse the graph from vertex v
void GraphAdjArray::DFSTree(int v, PCSTreeNode t, bool* visited)
{
	visited[v] = true;
	bool first = true;

	CSTreeNode *p = NULL, *q = NULL;
	int w;
	for(w = FirstAdjVertex(v); w >= 0; w = NextAdjVertex(v, w))
	{
		if(visited[w])
		{
			continue;
		}

		p = new CSTreeNode(&vexs[w]);
		if(first)
		{
			t->firstchild = p;
			first = false;
		}
		else
		{
			assert(q != NULL);
			q->nextsibling = p;
		}
		q = p;

		DFSTree(w, p, visited);
	}
}
