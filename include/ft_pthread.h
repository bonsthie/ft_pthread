#ifndef FT_PTHREAD_H
#define FT_PTHREAD_H

#include <stdint.h>

#include "internal/ft_pthread_mutex.h"
#include "internal/ft_pthread_attr.h"

#define __FT_PTHREAD_ALIGMENT __attribute__((aligned(32)))

typedef uintptr_t t_pthread;

typedef struct {
    char __size[__FT_PTHREAD_ATTR_SIZE];
} t_pthread_attr __FT_PTHREAD_ALIGMENT;

typedef struct {
    char __size[__FT_PTHREAD_MUTEX_SIZE];
} t_pthread_mutex __FT_PTHREAD_ALIGMENT;

typedef struct {
	char __size[__FT_PTHREAD_MUTEX_ATTR_SIZE];
} t_pthread_mutexattr __FT_PTHREAD_ALIGMENT;

t_pthread *ft_pthread_self(void);

int ft_pthread_attr_init(t_pthread_attr *attr); // TODO

int ft_pthread_attr_destroy(t_pthread_attr *attr); // TODO

int ft_pthread_create(t_pthread *__restrict__ thread, const t_pthread_attr *__restrict__ attr,
                      void *(*start_routine)(void *), void *__restrict__ arg);

int ft_pthread_join(t_pthread *thread, void **value_ptr);

int ft_tsprintf(const char *format, ...) __attribute__((format(printf, 1, 2)));

/* mutex */

int ft_pthread_mutex_init(t_pthread_mutex *mutex, t_pthread_mutexattr *attr); // TODO

int ft_pthread_mutex_destroy(t_pthread_mutex *mutex); // TODO

int ft_pthread_mutexattr_init(t_pthread_mutexattr *attr); // TODO

int ft_pthread_mutexattr_destroy(t_pthread_mutexattr *attr); // TODO

#endif /* FT_PTHREAD_H */
