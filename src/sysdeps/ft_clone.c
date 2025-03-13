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
    int tid = ft_syscall(SYS_clone3, clone_args, sizeof(struct clone_args));
    if (tid == -1)
    {
        return -1;
    } else if (tid == 0)
    {
        int ret = fn(args);
        _exit(ret);
    }
    return tid;
}
