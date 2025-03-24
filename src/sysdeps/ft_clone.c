#include "ft_pthread.h"
#include <errno.h>
#include <linux/sched.h>
#include <syscall.h>
#include <unistd.h>

int clone(int (*fn)(void *), void *child_stack, int flags, void *args);

int ft_clone(int (*fn)(void *), void *child_stack, int flags, void *args)
{
    return clone(fn, child_stack, flags, args);
}

int __clone3(struct clone_args *cl_args, size_t cl_args_size, int (*fn)(void *args), void *args);

int ft_clone3(struct clone_args *cl_args, size_t cl_args_size, int (*fn)(void *args), void *args)
{
	return __clone3(cl_args, cl_args_size, fn, args);
}
