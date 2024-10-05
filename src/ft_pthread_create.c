#include "ft_pthread.h"

 int ft_pthread_create(t_pthread *__restrict__ thread,
                          const t_pthread_attr *__restrict__ attr,
                          void *(*start_routine)(void *),
                          void *__restrict__ arg)
{
	(void)thread;
	(void)attr;
	(void)start_routine;
	(void)arg;
	return (1);
}
