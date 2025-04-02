#ifndef __PTHREAD_MUTEX_H
#define __PTHREAD_MUTEX_H

#include "ft_pthread.h"

typedef struct __pthread_mutex {
    t_pthread   *owner;
    volatile int lock;
} __pthread_mutex;

#endif /* __PTHREAD_MUTEX_H */
