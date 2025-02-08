#include "ft_pthread.h"
#include "sysdeps/ft_futex.h"
#include <stdio.h>

int ft_pthread_join(t_pthread *thread, void **value_ptr)
{
    ft_tsprintf("[%p](id : %d) start join \n", thread, *(int *)thread->arg);
    while (atomic_load(&thread->thread_status) != TH_JOINABLE)
    {
        int current_state = atomic_load(&thread->thread_status);

        if (current_state != TH_JOINABLE)
        {
            ft_tsprintf("[%p](id : %d) before wait \n", thread, *(int *)thread->arg);
            if (ft_futex_wait((int *)&thread->thread_status, current_state) == -1)
                return 1;
            ft_tsprintf("[%p](id : %d) after wait \n", thread, *(int *)thread->arg);
        }
    }

    if (value_ptr != NULL)
        *value_ptr = thread->ret;

    ft_tsprintf("[%p](id : %d) end join \n", thread, *(int *)thread->arg);

    return 0;
}
