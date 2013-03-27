#include "Utils.h"
#include <string.h>
#include <stdio.h>

static const char* LINE_SEPARATOR = "===========================================================";

void PrintSep()
{
	printf("%s\n", LINE_SEPARATOR);
}
void PrintSep(const char* str)
{
	if(str == NULL)
	{
		PrintSep();
		return;
	}
	const char* filename = GetFileName(str);
	int len = strlen(filename);
	int sep_len = strlen(LINE_SEPARATOR);
	int half_len = (sep_len - len) / 2;

	char buf[256];
	strcpy(buf, LINE_SEPARATOR);
	memcpy(buf + half_len, filename, len);
	printf("%s\n", buf);
}
const char* GetFileName(const char* fullFileName)
{
	char* ret = strrchr(fullFileName, '\\');
	if(ret == NULL)
	{
		return fullFileName;
	}
	else
	{
		return ret + 1;
	}
}