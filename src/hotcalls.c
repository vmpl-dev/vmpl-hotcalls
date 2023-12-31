#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>

#include "hotcalls.h"
#include "hot_calls.h"

HotCall hotcall = HOTCALL_INITIALIZER;
static HotCallTable callTable;

void my_syscall(void* syscall_args)
{
    hotcall_args_t *args = (hotcall_args_t *)syscall_args;
    args->rax = syscall(args->sysnr, args->rdi, args->rsi,
                        args->rdx, args->r10, args->r8, args->r9);
}

void hotcalls_thread(void* args)
{
    HotCall_waitForCall((HotCall*)args, &callTable);
}

void hotcalls_setup(int max_entries)
{
    callTable.numEntries = max_entries;
    callTable.callbacks = (SyscallFunction*)malloc(sizeof(SyscallFunction) * max_entries);
    for(int i = 0; i < max_entries; i++)
        callTable.callbacks[i] = NULL;
    hotcalls_register(0, my_syscall);
    pthread_create(&(hotcall.responderThread), NULL, (void *(*)(void *))hotcalls_thread, (void *)&hotcall);
}

int hotcalls_register(int sysnr, SyscallFunction func)
{
    if(sysnr >= callTable.numEntries)
        return EXIT_FAILURE; //fail to register

    callTable.callbacks[sysnr] = func;
    return EXIT_SUCCESS;
}

int hotcalls_teardown()
{
    StopResponder(&hotcall);
    if(hotcall.keepPolling)
        return EXIT_FAILURE; //fail to teardown
    
    return EXIT_SUCCESS; //success
}

long hotcalls_call(hotcall_args_t *args)
{
    HotCall_requestCall(&hotcall, (uint16_t)0, args);
    return ((hotcall_args_t *)hotcall.data)->rax;
}

long syscalls_call(hotcall_args_t *args)
{
    args->rax = syscall(args->sysnr, args->rdi, args->rsi,
                   args->rdx, args->r10, args->r8, args->r9);
    return args->rax;
}