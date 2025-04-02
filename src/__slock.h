/* slock func are simple optimise mutex witout protection */

#include "__ft_pthread_mutex.h"
#include "sysdeps/ft_futex.h"
#include <sys/cdefs.h>

static void __always_inline __slock(__pthread_mutex *mutex)
{
    do
    {
        if (__sync_bool_compare_and_swap(&mutex->lock, 0, 1))
            return;
        ft_futex_wait((int *)&mutex->lock, 1);

    } while (1);
}

static void __always_inline __sunlock(__pthread_mutex *mutex)
{
    if (__sync_bool_compare_and_swap(&mutex->lock, 1, 0))
        ft_futex_wake((int *)&mutex->lock, 1);
}

static void __always_inline __strylock(__pthread_mutex *mutex)
{
    __sync_bool_compare_and_swap(&mutex->lock, 0, 1);
}
