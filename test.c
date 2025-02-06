#include "include/ft_pthread.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *thread_routine(void *data)
{
	static pthread_mutex_t oui;
	
	pthread_mutex_lock(&oui);
	printf("%d\n", *(int *)data);
	pthread_mutex_unlock(&oui);
	return (NULL);
}

int main()
{
    t_pthread yes[10];
    int *thread_ids = malloc(10 * sizeof(int));

    for (int i = 0; i < 10; i++) {
        thread_ids[i] = i;
        ft_pthread_create(&yes[i], NULL, thread_routine, &thread_ids[i]);
    }

    for (int i = 0; i < 10; i++) {
		printf("id %d == %d\n", thread_ids[i], yes[i].tid);
    }

	/* printf("caca\n"); */
	/*     for (int i = 0; i < 10; i++) { */
	/* 	printf("id %d == %ld\n", thread_ids[i], yes[i]); */
		/* ft_pthread_join(yes[i], NULL); */
	/*     } */

    return 0;
}
