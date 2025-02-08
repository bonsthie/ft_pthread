#include <stdio.h>
#include <ft_pthread.h>
#include <stdatomic.h>
#include <syscall.h>
#include <time.h>

#define TH_STATUS(x) x == 1 ? "TH_JOINABLE" : "TH_RUNNING"

#include "ft_futex.h"

int ft_futex(int *uaddr, int futex_op, int val, const struct timespec *timeout, int *uaddr2, int val3)
{
    return ft_syscall(SYS_futex, uaddr, futex_op, val, timeout, uaddr2, val3);
}

/* int futex_wait_op(int *uaddr, int val, int val3) */

int ft_futex_wait(int *uaddr, int val) 
{
	/* ft_tsprintf("[futex] Thread is %s\n", TH_STATUS(val)); */
    /* ft_tsprintf("[futex] Thread %p waiting on futex [value === %s]\n", ft_syscall(SYS_gettid), TH_STATUS(atomic_load((atomic_int *)uaddr))); */
	int ret = ft_futex(uaddr, FUTEX_WAIT, val, NULL, NULL, 0);
    /* ft_tsprintf("[futex] Thread %p resume [value === %s]\n", ft_syscall(SYS_gettid), TH_STATUS(atomic_load((atomic_int *)uaddr))); */
	return ret;
}


int ft_futex_wake(int *uaddr, int val) 
{
    /* ft_tsprintf("[futex] Thread %p waking up [value === %s]\n", ft_syscall(SYS_gettid), TH_STATUS(atomic_load((atomic_int *)uaddr))); */
	return ft_futex(uaddr, FUTEX_WAKE, val, NULL, NULL, 0);
}

