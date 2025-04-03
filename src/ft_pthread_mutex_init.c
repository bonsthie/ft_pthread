
#include "__ft_pthread_mutex.h"
#include <ft_pthread.h>

int ft_pthread_mutex_init(t_pthread_mutex *mutex, t_pthread_mutexattr *attr)
{
    *mutex = (t_pthread_mutex){0};

    if (attr)
    {
        __pthread_mutex_attr *iattr = (__pthread_mutex_attr *)attr;
        __pthread_mutex      *imutex = (__pthread_mutex *)mutex;

        imutex->type = iattr->type;
    }

    return 0;
}
