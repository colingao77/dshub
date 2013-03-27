#ifndef __CS_TREE_NODE_H__
#define __CS_TREE_NODE_H__

#include "TreeNode.h"

//Tree Node represented by First Child and Next Sibling form
class CSTreeNode : public TreeNode
{
public:
	void* data;
	CSTreeNode *firstchild, *nextsibling;
	CSTreeNode *parent;
public:
	CSTreeNode(void* _data = NULL);
	virtual ~CSTreeNode();
	
	//Data Operation
	virtual void SetData(void* ptr);
	virtual void* GetData();
	
	//Enumeration Operations
	virtual bool PreOrderEnum(EnumProc pProc, void* lParam);
	virtual bool PostOrderEnum(EnumProc pProc, void* lParam);
	virtual bool BFSEnum(EnumProc pProc, void* lParam);
};

typedef CSTreeNode *CSTree, *PCSTreeNode;

#endif