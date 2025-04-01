#ifndef __FT_PTHREAD_H
#define __FT_PTHREAD_H

#include <ft_pthread.h>
#include <stdint.h>

#define DEFAULT_STACK_SIZE (8192 * 1024)
#define ALIGN_SIZE 16
#define ALIGN(x) (((x) + ALIGN_SIZE - 1) & ~(ALIGN_SIZE - 1))

#define THREAD_SIZE (ALIGN(sizeof(__pthread)))

typedef void *(*t_pthread_routine)(void *);

enum thread_status {
    TH_RUNNING,
    TH_JOINABLE,
};

typedef struct __pthread {
    // need to be at offset 0 to store in %fs register
    // for ft_pthread_self
    // change this part will break the ABI
    struct __pthread *tcb;
    void             *dtv;
    struct __pthread *self;

    // thread settings
    // will not break the ABI
    void *tls;
    void *mapped_region;
    int   mapped_size;
    void *stack;
    int   stack_size;
    int   tls_size;

    int               tid;
    int               id;
    t_pthread_routine routine;
    atomic_int        thread_status;
    t_pthread_attr    attr;

    // user settings

    void *arg;
    void *ret;
} __pthread;

#endif /* __FT_PTHREAD_H */
