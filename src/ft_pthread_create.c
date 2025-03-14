#include "__ft_pthread.h"
#include "ft_pthread.h"
#include "ft_pthread_log.h"
#include "sysdeps/ft_futex.h"
#include "sysdeps/ft_mman.h"
#include "sysdeps/ft_pthread_arch.h"
#include "sysdeps/ft_sched.h"
#include <asm-generic/param.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#define _GNU_SOURCE
#include <sched.h>
#include <unistd.h>

static int get_stack_size(const t_pthread_attr *attr)
{
    if (attr)
        return ALIGN(attr->stack_size);
    else
        return (DEFAULT_STACK_SIZE);
}

static void *ft_pthread_create_stack(uint32_t stack_size)
{
    void *stack;

    stack = ft_mmap(NULL, stack_size, PROT_RW, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (!stack)
        return (NULL);
    /* if (ft_mprotect(stack, EXEC_PAGESIZE, PROT_NONE) == -1) */
    /* { */
    /*     ft_munmap(stack, stack_size); */
    /*     return (NULL); */
    /* } */
    return (stack);
}

int start_thread(void *data)
{
    __pthread *thread;

    ft_pthread_log_self("start thread pogger");

    thread = data;
    thread->thread_status = TH_RUNNING;
    thread->ret = thread->routine(thread->arg);
    ft_pthread_log_self("end thread");
    thread->thread_status = TH_JOINABLE;

    ft_futex_wake((int *)&thread->thread_status, TH_JOINABLE);

    return 0;
}

static void assign_thread_id(__pthread *thread)
{
    static volatile int id = 0;

    thread->id = id;
    id++;
}

static int alloc_and_map_stack(__pthread **tp, const t_pthread_attr *attr)
{
    int stack_size = get_stack_size(attr);
    int tls_size = 1024 * 1024; // TO CHANGE

    int total_size = ALIGN(stack_size + tls_size + THREAD_SIZE);

    void *map = ft_pthread_create_stack(total_size);
    if (map == NULL)
        return 1;

    *tp = map;
    __pthread *new = *tp;

    memset(new, 0, THREAD_SIZE);
	new->tcb = new;
    new->self = new;

    new->mapped_size = total_size;
    new->mapped_region = map;
    new->tls = map + THREAD_SIZE;
    new->tls_size = tls_size;
    memset(new->tls, 0, tls_size);

    new->stack = map + total_size;
    new->stack_size = stack_size;

    return 0;
}

int ft_pthread_create(t_pthread *__restrict__ thread, const t_pthread_attr *__restrict__ attr,
                      void *(*start_routine)(void *), void *__restrict__ arg)
{
    __pthread *new;

    int err = alloc_and_map_stack(&new, attr);
    if (err == 1)
    {
        // set errno and other;
        return 1;
    }
    *thread = (t_pthread) new;

    new->routine = start_routine;
    new->arg = arg;
    assign_thread_id(new);

    ft_pthread_log(thread, "start create");

    const int clone_flags = //

        /*
         * If CLONE_VM is set, parent and child share the same memory space; otherwise, the child
         * gets a separate copy like fork.
         */
        (CLONE_VM

         /*
          * share the same filesystem information
          * (if not set clone create a copy of the fs)
          */
         | CLONE_FS

         /*
          * share the same file descriptor table
          */
         | CLONE_FILES

         /*
          * makes the parent and child share System V semaphore adjustments, meaning semaphore
          * changes affect both. Without it, the child gets a new, empty semaphore adjustment list.
          */
         | CLONE_SYSVSEM

         /*
          * parent and child share signal handlers but have separate signal masks and pending
          * signals
          */
         | CLONE_SIGHAND

         /*
          * If CLONE_THREAD is set, the child joins the parent's thread group, sharing the same PID
          * (TGID), signal disposition, and parent but maintaining a unique TID and signal mask.
          */
         | CLONE_THREAD

         /*
          * Set the TLS descriptor to .tls, with architecture-dependent
          * interpretation. (x86_64 %fs register)
          */
         | CLONE_SETTLS

         /*
          * Store the child thread ID at .parent_tid in parent memory before
          * returning to user space.
          */
         | CLONE_PARENT_SETTID

         /*
          * Clear and wake the futex at .child_tid in child memory on exit.
          */
         | CLONE_CHILD_CLEARTID //
        );

    struct clone_args args = {
        .flags = clone_flags,
        .pidfd = (uintptr_t)&new->tid,
        .parent_tid = (uintptr_t)&new->tid,
        .child_tid = (uintptr_t)&new->tid,

        // pointer to the top of the stack for clone3() insted of
        // the bottom for clone()
        .stack = (uintptr_t)new->stack,
        .stack_size = new->stack_size,

        .tls = (uintptr_t)new,
    };

    int tid = ft_clone3(start_thread, new, &args);

    if (tid == -1)
    {
        ft_pthread_log(thread, "fail create");
        ft_munmap(new->mapped_region, new->mapped_size);
        return (-1);
    }
    ft_pthread_log(thread, "end create");
    return 0;
}
