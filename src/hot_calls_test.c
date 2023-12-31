#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <sys/syscall.h>

#include "hotcalls.h"

int hotcalls_write(int fd, const void *buf, size_t count)
{
    hotcall_args_t args = {
        .sysnr = SYS_write,
        .rdi = fd,
        .rsi = (uint64_t)buf,
        .rdx = count,
    };
    return hotcalls_call(&args);
}

int main(int argc, char *argv[]) {
    printf("enter main...\n");
    hotcalls_setup(1);
    printf("setup finish \n");
    hotcalls_write(1, "hello world\n", 12);
    printf("call finish \n");
    hotcalls_teardown();
    return 0;
}