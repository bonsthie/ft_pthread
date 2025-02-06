#include <syscall.h>

int	clone(int (*fn)(void *), void *child_stack, int flags, void *arg);

int	ft_clone(int (*fn)(void *), void *child_stack, int flags, void *arg)
{
	return clone(fn, child_stack, flags, arg);
}
