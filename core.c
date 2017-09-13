/**********************************************************
 * Author        : nfalse
 * Email         : nfalse@163.com
 * Last modified : 2017-09-13 16:25
 * Filename      : core.c
 * Description   :
 * *******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
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
//register unsigned long sp asm("sp");
//register unsigned long bp asm("bp");
void hook_func(void *obj)
{
    printf("恶意代码被调用\n");
    exit(0);
}
void stack_overflow_target(char* str)
{
    char p;
    printf("$rbp %p\n",&p + sizeof(p));
    printf("return address %p\n",(void*)*(long*)(&p + sizeof(p) +sizeof(void*)));
    printf("hook address %p\n",(void*)hook_func);
    printf("正常代码调用\n");
    strcpy(&p,str);
    printf("return address %p\n",(void*)*(long*)(&p + sizeof(p) + sizeof(void*)));
    return;
}
void stack_overflow_test()
{
    int buffer_size = (sizeof(char)+sizeof(void*)+sizeof(void*)+1);
    char over[buffer_size];
    memset(over,'A',buffer_size - 1);
    over[buffer_size] ='\0';
    long addres=(long)hook_func;
    memcpy(over+buffer_size-8-1,&addres,sizeof(addres));
    stack_overflow_target(over);
}
struct chunk_structure {
    size_t prev_size;
    size_t size;
    struct chunk_structure *fd;
    struct chunk_structure *bk;
    char padding[10];               // padding
};
void heap_overflow_test()
{
    return;
}
typedef void (*func_ptr)(void *);
void echo(void *content)
{
    printf("%s",(char *)content);
}
#define index 128
void ufa()
{
    func_ptr *p1= malloc(8192);
    printf("p1[%p]\n",p1);
    p1[index]=echo;
    p1[index]("hello world\n");
    free(p1);
    printf("p1[%p] free\n",p1);
    p1[index]("hello world affter free\n");
    func_ptr *p2= malloc(8192);
    printf("p2[%p]\n",p2);
    p2[3]=hook_func;
    p1[3](NULL);
    return;
}
int main(int argc,char **argv)
{
    int ch;  
    opterr = 0;  
    while ((ch = getopt(argc,argv,"shu"))!=-1)  
    {  
        switch(ch)  
        {  
        case 's':  
            stack_overflow_test();
            goto end;
        case 'h':
            heap_overflow_test();
            goto end;
        case 'u':
            ufa();
            goto end;
        default:
            break;
        }  
    }
    printf("%s -s -h -u\n",argv[0]);
    return -1;
end:
    return 0;
}
