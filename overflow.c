/**********************************************************
 * Author        : nfalse
 * Email         : nfalse@163.com
 * Last modified : 2016-05-04 14:38
 * Filename      : overflow.c
 * Description   : 
 * *******************************************************/
#include <stdio.h>
#include <string.h>
#define LEN 8
void funcA(char* str)
{
	char tmp[LEN];
	strcpy(tmp,str);
}
void funcB()
{
	printf("恶意代码被调用\n");
}
void main()
{
	char over[LEN+24];
	memset(over,'F',sizeof(over));
	*(long*)&over[LEN+16]=(long)funcB;
	funcA(over);
}
