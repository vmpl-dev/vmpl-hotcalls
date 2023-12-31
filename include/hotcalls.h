#include <stdio.h>
#include <string.h>
#include <assert.h>
#include<pthread.h>
#include <sys/syscall.h>
#include <unistd.h>
#include"hot_calls.h"

typedef struct
{
    int sysnr;
    uint64_t rax;
    uint64_t rdi;
    uint64_t rsi;
    uint64_t rdx;
    uint64_t r10;
    uint64_t r8;
    uint64_t r9;
} hotcall_args_t;

// 函数指针类型，用于表示系统调用函数
typedef void (*SyscallFunction)(void* args);

/**
 * 创建hotcalls线程，随时准备接收hotcalls请求:
 * 执行syscall转发循环，从共享内存获取 struct hotcall args_t 参数，并将返回值通过共享内存返回给调用者
 * 在VMPL0初始化的时候会调用该函数，以创建一个hotcalls线程;
 * 线程会等待hotcalls请求，直到调用hotcalls teardown()结束线程
*/
void hotcalls_setup();

/**
 * 关闭hotcalls线程，释放hotcalls线程资源
 * 
 * @return int 表示线程是否顺利结束 1表示顺利结束
*/
int hotcalls_teardown();

/**
 * @brief 调用hotcalls，将参数传递给hotcals线程，hotalls线程执行syscall，将返回值通过共享内存返回给调用者
 * @param sysnr 系统调用号
 * @param args 系统调用参数
 * @return int 系统调用返回值
*/
int hotcalls_call(hotcall_args_t *args);

