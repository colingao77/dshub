#include <stdlib.h>
#include <stdio.h>
#include "test.h"

int main(int argc, char* argv[])
{
	printf("main start\n\n");

	TestCSTreeNode();
	TestGraphAdjArray();
	TestGraphAdjList();

	printf("\nmain end\n");
	return 0;
}