#include "GraphAdjList.h"
#include <string.h>

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

bool GraphAdjList::InitByMatrix(FILE* stream)
{
	if(stream == NULL)
	{
		printf("null input stream\n");
		return false;
	}
	
	int ret, val, i, j, cost;
	char c;
	ret = fscanf(stream, "%d%c", &val, &c);
	if(ret != 2)
	{
		printf("invalid format: vertex num invalid\n");
		return false;
	}
	
	for(i = 0; i < val; i++)
	{
		vexs[i].vertex = i;

		for(j = 0; j < val; j++)
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

			InsertArc(i, j, cost);
		}
	}
	
	vexnum = val;
	
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
	
	for(i = 0; i < n; i++)
	{
		ret = fscanf(stream, "%d %d %d", &x, &y, &cost);
		if(ret != 3)
		{
			printf("invalid format: %d edge invalid\n", i);
			return false;
		}
		fscanf(stream, "%c", &c);

		InsertArc(x, y, cost);
		InsertArc(y, x, cost);
	}
	
	vexnum = m;
	
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
			if((vexs[i].vertex <= pArc->adjvex) || all)
			{
				printf("%2d %2d %2d\n", vexs[i].vertex, pArc->adjvex, pArc->arcinfo.cost);
			}
			
			pArc = pArc->nextarc;
		}
	}
}

void GraphAdjList::InsertArc(int from, int to, int cost)
{
	vexs[from].vertex = from;

	ArcNode* pArc = new ArcNode();
	pArc->adjvex = to;
	pArc->arcinfo.cost = cost;
	pArc->nextarc = NULL;

	if(vexs[from].firstarc == NULL)
	{
		vexs[from].firstarc = pArc;
	}
	else
	{
		//TODO: cache the tail pointer to make the insert operation complete at O(1)
		ArcNode* pTail = vexs[from].firstarc;
		while(pTail->nextarc != NULL)
		{
			pTail = pTail->nextarc;
		}
		pTail->nextarc = pArc;
	}

	arcnum++;
}