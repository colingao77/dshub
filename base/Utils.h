#ifndef __UTILS_H__
#define __UTILS_H__

#include "config.h"

#ifndef COUNT_OF
#define COUNT_OF(A)	(sizeof(A)/sizeof(A[0]))
#endif

void PrintSep();
void PrintSep(const char* str);
const char* GetFileName(const char* fullFileName);

#endif