#include "ft_pthread.h"
#include "sysdeps/ft_futex.h"
#include <stdio.h>

int ft_pthread_join(t_pthread *thread, void **value_ptr) {
    while (atomic_load(&thread->thread_status) != TH_JOINABLE) {
        int current_state = atomic_load(&thread->thread_status);

		printf("yes");
        if (current_state != TH_JOINABLE) {
            if (ft_futex_wait((int *)&thread->thread_status, current_state) == -1) {
                return -1;
            }
        }
    }

    if (value_ptr != NULL) {
        *value_ptr = thread->ret;
    }

    return 0;
}
