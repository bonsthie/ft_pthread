#include "ft_pthread.h"
#include <syscall.h>
#include <stdlib.h>

int ft_clone(int (*fn)(void *), void *child_stack, int flags, void *arg)
{
	/* void *stack_top = child_stack; */

    /* stack_top -= sizeof(t_pthread); */
    /* (t_pthread *)stack_top = arg; */

	pid_t pid = ft_syscall(SYS_CLONE, flags, child_stack);

	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		int ret = fn(arg);
		exit(ret);
	}
	return (pid);
}
