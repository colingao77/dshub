#include "GraphAdjArray.h"
#include <string.h>
#include <queue>

GraphAdjArray::GraphAdjArray() : kind(UDG), vexnum(0), arcnum(0)
{
	memset(vexs, 0, sizeof(vexs));
	memset(arcs, 0, sizeof(arcs));
}

GraphAdjArray::~GraphAdjArray()
{

}

bool GraphAdjArray::InitByMatrix(FILE* stream)
{
	if(stream == NULL)
	{
		printf("null input stream\n");
		return false;
	}

	int ret, val, i, j;
	char c;
	ret = fscanf(stream, "%d%c", &val, &c);
	if(ret != 2)
	{
		printf("invalid format: vertex num invalid\n");
		return false;
	}

	for(i = 0; i < val; i++)
	{
		for(j = 0; j < val; j++)
		{
			ret = fscanf(stream, "%d", &(arcs[i][j].cost));
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

			if(arcs[i][j].cost != 0)
			{
				arcnum++;
			}
		}
	}

	vexnum = val;

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

	for(i = 0; i < m; i++)
	{
		for(j = 0; j < m; j++)
		{
			arcs[i][j].cost = 0;
		}
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

		arcs[x][y].cost = cost;
		arcs[y][x].cost = cost;
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

void GraphAdjArray::DFS(GraphEnumProc pProc, void* lParam)
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
}

bool GraphAdjArray::DFS(GraphEnumProc pProc, void* lParam, int vertex, bool* visited)
{
	visited[vertex] = true;
	if(!pProc(vertex, lParam))
	{
		return false;
	}

	int i;
	for(i = 0; i < vexnum; i++)
	{
		if(arcs[vertex][i].cost != 0 && !visited[i])
		{
			if(!DFS(pProc, lParam, i, visited))
			{
				return false;
			}
		}
	}
	return true;
}

void GraphAdjArray::BFS(GraphEnumProc pProc, void* lParam)
{
	if(vexnum <= 0)
	{
		return;
	}
	bool* visited = new bool[vexnum];
	memset(visited, 0, sizeof(bool) * vexnum);

	std::queue<int> que;
	int i, j, u;
	for(i = 0; i <vexnum; i++)
	{
		if(visited[i])
		{
			continue;
		}
		visited[i] = true;
		if(!pProc(i, lParam))
		{
			return;
		}

		que.push(i);
		while(!que.empty())
		{
			u = que.front();
			que.pop();

			for(j = 0; j < vexnum; j++)
			{
				if(arcs[u][j].cost != 0 && !visited[j])
				{
					visited[j] = true;
					if(!pProc(j, lParam))
					{
						return;
					}
					que.push(j);
				}
			}
		}
	}
}

