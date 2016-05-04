/**********************************************************
 * Author        : nfalse
 * Email         : nfalse@163.com
 * Last modified : 2016-05-04 15:35
 * Filename      : overflow.c
 * Description   : 
 * *******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 8
void funcA(char* str)
{
	printf("正常代码调用\n");
	char tmp[LEN];
	strcpy(tmp,str);
	return;
}
void funcB(void *obj)
{
	printf("恶意代码被调用\n");
	exit(0);
	return;
}
void main()
{
	char over[LEN+24];
	memset(over,'F',sizeof(over));
	*(long*)&over[LEN+16]=(long)funcB;
	funcA(over);
}
