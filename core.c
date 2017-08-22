/**********************************************************
 * Author        : nfalse
 * Email         : nfalse@163.com
 * Last modified : 2017-08-22 11:48
 * Filename      : overflow.c
 * Description   : 
 * *******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if defined(__arm__)
#if defined(__ARM_ARCH_7A__)
#if defined(__ARM_NEON__)
#if defined(__ARM_PCS_VFP)
#define ABI "armeabi-v7a/NEON (hard-float)"
#else
#define ABI "armeabi-v7a/NEON"
#endif
#else
#if defined(__ARM_PCS_VFP)
#define ABI "armeabi-v7a (hard-float)"
#else
#define ABI "armeabi-v7a"
#endif
#endif
#else
#define ABI "armeabi"
#endif
#elif defined(__i386__)
#define ABI "x86"
#elif defined(__x86_64__)
#define ABI "x86_64"
#elif defined(__mips64)
#define ABI "mips64"
#elif defined(__mips__)
#define ABI "mips"
#elif defined(__aarch64__)
#define ABI "arm64-v8a"
#else
#define ABI "unknown"
#endif
#define nop 9       //$rbp - &p + sizeof(p)
void funcA(char* str)
{
    char p;
    printf("正常代码调用\n");
    strcpy(&p,str);
    return;
}
void funcB(void *obj)
{
    printf("恶意代码被调用\n");
    exit(0);
}
void main()
{
    char over[nop+sizeof(void*)+1];
    memset(over,'A',nop);
    over[nop+sizeof(void*)] ='\0';
    long addres=(long)funcB;
    memcpy(over+nop,&addres,sizeof(addres));
    funcA(over);
}
