#include "ft_pthread.h"
#include "sysdeps/ft_mman.h"
#include <asm-generic/param.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include "sysdeps/ft_sched.h"
#include <sched.h>

#include <unistd.h>

#define DEFAULT_STACK_SIZE 8192

static int get_stack_size(const t_pthread_attr *attr)
{
	if (attr)
		return (attr->stack_size);
	else
		return (DEFAULT_STACK_SIZE);

}

static void	*ft_pthread_create_stack(uint32_t stack_size)
{
	void	*stack;

	stack = ft_mmap(NULL, stack_size, PROT_RW, MAP_PRIVATE | MAP_ANONYMOUS, -1,
			0);
	if (!stack)
		return (NULL);
	if (ft_mprotect(stack, EXEC_PAGESIZE, PROT_NONE) == -1)
	{
		ft_munmap(stack, stack_size);
		return (NULL);
	}
	return (stack);
}

static int start_thread(void *data)
{
	t_pthread *thread;
	void		*ret;

	thread = data;
	ret =  thread->routine(thread->arg);
	(void)ret;
	return (0);
}

int	ft_pthread_create(t_pthread *__restrict__ thread,
		const t_pthread_attr *__restrict__ attr, void *(*start_routine)(void *),
		void *__restrict__ arg)
{
	void *stack;
	uint32_t stack_size;

	stack_size = get_stack_size(attr);
	stack = ft_pthread_create_stack(stack_size);
	if (!stack)
		return (-1);

	thread->routine = start_routine;
	thread->arg = arg;
	int flags =  CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SYSVSEM | CLONE_SIGHAND | CLONE_THREAD;
	int tid = clone(start_thread, stack, flags, thread); 
	if (tid < 0)
	{
		ft_munmap(stack, attr->stack_size);
		free(thread);
		return (tid);
	}
	return (1);
}
