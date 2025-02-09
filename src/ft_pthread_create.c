#include "ft_pthread.h"
#include "sysdeps/ft_futex.h"
#include "sysdeps/ft_mman.h"
#include "sysdeps/ft_pthread_arch.h"
#include "sysdeps/ft_sched.h"
#include <asm-generic/param.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "ft_pthread_log.h"

#define _GNU_SOURCE
#include <sched.h>
#include <unistd.h>

#define DEFAULT_STACK_SIZE (8192 * 1024)

static int get_stack_size(const t_pthread_attr *attr)
{
    if (attr)
        return (attr->stack_size + 15) & ~15;
    else
        return (DEFAULT_STACK_SIZE);
}

static void *ft_pthread_create_stack(uint32_t stack_size)
{
    void *stack;

    stack = ft_mmap(NULL, stack_size, PROT_RW, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (!stack)
        return (NULL);
    if (ft_mprotect(stack, EXEC_PAGESIZE, PROT_NONE) == -1)
    {
        ft_munmap(stack, stack_size);
        return (NULL);
    }
    return (stack);
}

int start_thread(void *data)
{
    t_pthread *thread;

    __set_tp((uintptr_t)data);

	__ft_pthread_log_self("start thread pogger");

	thread = data;
	atomic_store_explicit(&thread->thread_status, TH_RUNNING, memory_order_release);
    thread->ret = thread->routine(thread->arg);
	__ft_pthread_log_self("end thread");
	atomic_store_explicit(&thread->thread_status, TH_JOINABLE, memory_order_release);

    ft_futex_wake((int *)&thread->thread_status, TH_JOINABLE);

    return 0;
}

static void assign_thread_id(t_pthread *thread)
{
    static int id = 0;

    thread->id = id;
    id++;
}

int ft_pthread_create(t_pthread *__restrict__ thread, const t_pthread_attr *__restrict__ attr,
                      void *(*start_routine)(void *), void *__restrict__ arg)
{
    void    *stack;
    uint32_t stack_size;

	memset(thread, 0, sizeof(t_pthread));
	thread->self = thread;
	thread->routine = start_routine;
	thread->arg = arg;
    assign_thread_id(thread);
	__ft_pthread_log(thread, "start create");


    stack_size = get_stack_size(attr);
    stack = ft_pthread_create_stack(stack_size);
    if (!stack)
        return (-1);

    int flags = CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SYSVSEM | CLONE_SIGHAND | CLONE_THREAD;
    thread->tid = ft_clone(start_thread, stack + stack_size, flags, thread);
    if (thread->tid < 0)
    {
        ft_munmap(stack, stack_size);
		__ft_pthread_log(thread, "fail create");
        return (thread->tid);
    }
	__ft_pthread_log(thread, "end create");
    return (0);
}
