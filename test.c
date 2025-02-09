#include "include/ft_pthread.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *thread_routine(void *data)
{
	int res;
	res = 0;
	for (int i = *(int *)data; i < 100000000; i++)
		res += i;

	sleep(5);
	/* ft_tsprintf("routine %d at [%p]\n", *(int *)data, data); */
	return ((void *)(long)res);
}

int main()
{
	t_pthread yes[5];
	int *thread_ids = malloc(5 * sizeof(int));

	for (int i = 0; i < 5; i++) {
		thread_ids[i] = i;
		ft_pthread_create(&yes[i], NULL, thread_routine, &thread_ids[i]);
	}
	


	for (int i = 0; i < 5; i++) {
		ft_pthread_join(&yes[i], NULL);
	}

	return 0;
}
