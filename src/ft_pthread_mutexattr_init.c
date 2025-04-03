#include "ft_pthread.h"

int ft_pthread_mutexattr_init(t_pthread_mutexattr *attr) {
	*attr = (t_pthread_mutexattr){0};
	return 0;
}
