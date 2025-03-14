#include "ft_pthread.h"
#include <linux/sched.h>
#include <syscall.h>
#include <unistd.h>

int clone(int (*fn)(void *), void *child_stack, int flags, void *arg);

int ft_clone(int (*fn)(void *), void *child_stack, int flags, void *arg)
{
    return clone(fn, child_stack, flags, arg);
}

int ft_clone3(int (*fn)(void *), void *args, struct clone_args *clone_args)
{
    ft_tsprintf("will clone thread\n");
    int tid = ft_syscall(SYS_clone3, clone_args, sizeof(struct clone_args));
    ft_tsprintf("after clone thread tid == %d\n", tid);
    if (tid < 0)
    {
        return -1;

    } else if (tid == 0)
    {
        ft_tsprintf("in the thread\n");
        fn(args);
        __builtin_unreachable();
    }
    ft_tsprintf("out the thread\n");
    return tid;
}
