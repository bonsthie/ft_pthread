
#include "__ft_pthread.h"
#include "ft_pthread.h"

int ft_pthread_attr_init(t_pthread_attr *attr) {
	__pthread_attr *iattr = (__pthread_attr *)attr;
	iattr->stack_size = DEFAULT_STACK_SIZE; // TODO change this for the loader size
	return 0;
}
