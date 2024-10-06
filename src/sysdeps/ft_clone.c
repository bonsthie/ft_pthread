#include <syscall.h>

int	ft_clone(int (*fn)(void *), void *child_stack, int flags, void *arg)
{
	return (ft_syscall(SYS_CLONE, fn, child_stack, flags, arg));
}
