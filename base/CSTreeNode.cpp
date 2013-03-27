#include "CSTreeNode.h"
#include <list>
#include "test.h"

CSTreeNode::CSTreeNode(void* ptr) : data(ptr), firstchild(NULL), nextsibling(NULL), parent(NULL)
{
}

CSTreeNode::~CSTreeNode()
{
}

//Data Operation
void CSTreeNode::SetData(void* ptr)
{
	data = ptr;
}
void* CSTreeNode::GetData()
{
	return data;
}

//Enumeration Operations
bool CSTreeNode::PreOrderEnum(EnumProc pProc, void* lParam)
{
	CSTreeNode *pNode = this, *pNext = this->firstchild;
	if(!pProc(this, lParam))
	{
		return false;
	}

	for(pNode = pNext; pNode != NULL; pNode = pNext)
	{
		pNext = pNode->nextsibling;
		if(!pNode->PreOrderEnum(pProc, lParam))
		{
			return false;
		}
	}
	return true;
}
bool CSTreeNode::PostOrderEnum(EnumProc pProc, void* lParam)
{
	CSTreeNode *pNode, *pNext;
	for(pNode = firstchild; pNode != NULL; pNode = pNext)
	{
		//if the current node is deleted, the field "nextsibling" will become wild pointer
		//save the "nextsibling" for later use
		pNext = pNode->nextsibling;
		if(!pNode->PostOrderEnum(pProc, lParam))
		{
			return false;
		}
	}

	if(!pProc(this, lParam))
	{
		return false;
	}

	return true;
}
bool CSTreeNode::BFSEnum(EnumProc pProc, void* lParam)
{
	std::list<CSTreeNode*> pNodeList;
	pNodeList.push_back(this);

	CSTreeNode *pNode, *pChild;
	while(!pNodeList.empty())
	{
		pNode = pNodeList.front();
		pNodeList.pop_front();

		if(!pProc(pNode, lParam))
		{
			return false;
		}

		for(pChild = pNode->firstchild; pChild != NULL; pChild = pChild->nextsibling)
		{
			pNodeList.push_back(pChild);
		}
	}
	
	return true;
}
