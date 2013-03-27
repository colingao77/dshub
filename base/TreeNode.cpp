#include "TreeNode.h"

TreeNode::TreeNode()
{
}

TreeNode::~TreeNode()
{
}

static bool DestroyProc(TreeNode* pNode, void* lParam)
{
	//Free Data if needed
	if(lParam)
	{
		//Free Data Procedure
		FreeProc pFreeProc = (FreeProc)lParam;
		
		//Free Data
		pFreeProc(pNode, pNode->GetData());
	}
	
	delete pNode;
	
	return true;
}

void DestoryTreeNode(TreeNode* pTreeNode, FreeProc pFreeProc, bool bIncludeChildren)
{
	if(pTreeNode == NULL)
	{
		return;
	}
	
	if(!bIncludeChildren)
	{
		DestroyProc(pTreeNode, pFreeProc);
	}
	else
	{
		pTreeNode->PostOrderEnum(DestroyProc, pFreeProc);
	}
}