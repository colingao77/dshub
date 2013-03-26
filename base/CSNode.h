#ifndef __CS_NODE_H__
#define __CS_NODE_H__

#include "config.h"

typedef int ElemType;

//Child and Sibling
class CSNode
{
public:
	ElemType data;
	CSNode *firstchild, *nextsibling;

public:
	CSNode(ElemType value = 0);
};

typedef CSNode* CSTree;

#endif