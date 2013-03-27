#ifndef __TREE_NODE_H__
#define __TREE_NODE_H__

#include "config.h"

class TreeNode;

typedef void (*FreeProc)(TreeNode* pNode, void* pData);

//return false to stop enumeration, else continue
typedef bool (*EnumProc)(TreeNode* pNode, void* lParam);

class TreeNode
{
public:
	TreeNode();
	virtual ~TreeNode();

	//Data Operation
	virtual void SetData(void* ptr) = 0;
	virtual void* GetData() = 0;
	
	//Enumeration Operations
	virtual bool PreOrderEnum(EnumProc pProc, void* lParam) = 0;
	virtual bool PostOrderEnum(EnumProc pProc, void* lParam) = 0;
	virtual bool BFSEnum(EnumProc pProc, void* lParam) = 0;
};

void DestoryTreeNode(TreeNode* pTreeNode, FreeProc pFreeProc, bool bIncludeChildren = true);

#endif