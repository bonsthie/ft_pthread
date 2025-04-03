#ifndef FT_PTHREAD_MUTEX_H
#define FT_PTHREAD_MUTEX_H

/* #if !defined(FT_PTHREAD_H) && !defined(__FT_PTHREAD_MUTEX_H) */
/* #    warning ("[internal/ft_pthread_mutex.h] this file should not be include directly") */
/* #endif */

// this is a tmp version for the dev of this lib the sizeof need to be replace by the hard coded
// version of the value and put the struct in the inside of the internal to completely hide the
// definition

#include <stdint.h>

typedef uintptr_t t_pthread;

struct __pthread_mutex_attr {
    uint32_t type;
};

struct __pthread_mutex {
    t_pthread   *owner;
    int          type;
    volatile int lock;
};

#define __FT_PTHREAD_MUTEX_SIZE sizeof(struct __pthread_mutex)
#define __FT_PTHREAD_MUTEX_ATTR_SIZE sizeof(struct __pthread_mutex_attr)

#endif /* FT_PTHREAD_MUTEX_H */
