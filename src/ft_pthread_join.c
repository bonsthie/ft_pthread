#include "ft_pthread.h"
#include "ft_pthread_log.h"
#include "sysdeps/ft_futex.h"
#include <errno.h>
#include <stdio.h>

int ft_pthread_join(t_pthread *thread, void **value_ptr)
{
    __ft_pthread_log(thread, "start join");
    while (atomic_load(&thread->thread_status) != TH_JOINABLE)
    {
        int current_state = atomic_load(&thread->thread_status);

        if (current_state != TH_JOINABLE)
        {
            __ft_pthread_log(thread, "before wait");
            if (ft_futex_wait((int *)&thread->thread_status, current_state) == -1)
                return 1;
			if (errno != EAGAIN) {
				__ft_pthread_log(thread, "join futex error [errno == EAGAIN]");
				return 1;
			}
            __ft_pthread_log(thread, "after wait");
        }
    }

    if (value_ptr != NULL)
        *value_ptr = thread->ret;

    __ft_pthread_log(thread, "end join sucess");

    return 0;
}
