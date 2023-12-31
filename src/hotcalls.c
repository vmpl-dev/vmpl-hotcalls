#include "hotcalls.h"



HotCall hotcall = HOTCALL_INITIALIZER;


void my_syscall(void* syscall_args)
{
    hotcall_args_t * args = (hotcall_args_t *)syscall_args;
    //todo
    //调用syscall，结果存在hotcall_args_t中的rax中
    args->rax = 0x111;
}

void hotcalls_thread(void* args)
{   
    void (*callbacks[1])(void*);
    callbacks[0] = my_syscall;

    HotCallTable callTable;
    callTable.numEntries = 1;
    callTable.callbacks  = callbacks;

    HotCall_waitForCall((HotCall*)args, &callTable);

}

void hotcalls_setup()
{
    pthread_create(&(hotcall.responderThread), NULL, (void *(*)(void *))hotcalls_thread, (void *)&hotcall);
}

int hotcalls_teardown()
{
    StopResponder(&hotcall);
    if(hotcall.keepPolling)
        return 0; //fail to teardown
    
    return 1; //success
}

int hotcalls_call(hotcall_args_t *args)
{
    printf("enter hotcalls_call\n");
    HotCall_requestCall(&hotcall, (uint16_t)0, args);
    return (int)((hotcall_args_t *)hotcall.data)->rax;
}

int main()
{
    (&hotcall)->spinlock;
    printf("enter main...\n");
    hotcalls_setup();
    printf("setup finish \n");
    
    hotcall_args_t args = {0,0,0,0,0,0,0,0};
    int rax = hotcalls_call(&args);
    //HotCall_requestCall(&hotcall, (uint16_t)0, (void*)&args);
    printf("call finish \n");
    hotcalls_teardown();
    printf("rax = %d\n",rax);
    return 0;
}