#include "include/ft_pthread.h"
#include "src/ft_pthread_log.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *__thread_routine(void *data)
{
	int res;
	ft_pthread_log_self("start routine");
	res = 0;
	for (int i = *(int *)data; i < 10000010; i++)
	{
	  if (i % 1000000 == 0)
		{
			ft_pthread_log_self("routine going i == %d", i);
			sleep(1);
		}
		res += i;
	}

	ft_pthread_log_self("end routine");
	(void)res;
	return NULL;
}

void *thread_routine(void *arg) {
    /* int id = *((int *)arg); */
    
	/* ft_tsprintf("Thread[%d]: Hello World!\n", id); */
	/* t_pthread *self = ft_pthread_self(); */
	/* ft_tsprintf("%p %p %d %d\n", self, self->self, self->id, self->tid); */

    // For example, add 10 to the id (you can change the computation as needed)
	int *nb = arg;

	*nb = *nb + 10;
    
    // Return the pointer to the result
    return NULL;
}

int main(void) {
	const int NUM_THREADS = 100;
	t_pthread threads[NUM_THREADS];
	//int thread_ids[NUM_THREADS];
	
	// Allocate an array to hold the thread id values.
	int *thread_ids = malloc(NUM_THREADS * sizeof(int));
	if (!thread_ids) {
		fprintf(stderr, "Failed to allocate memory for thread IDs\n");
		return EXIT_FAILURE;
	}
	
	// Create 10 threads.
	for (int i = 0; i < NUM_THREADS; i++) {
		thread_ids[i] = i;
		if (ft_pthread_create(&threads[i], NULL, thread_routine, &thread_ids[i]) != 0) {
			fprintf(stderr, "Error creating thread %d\n", i);
			free(thread_ids);
			return EXIT_FAILURE;
		}
	}
	
	// Join each thread and print its result.
	for (int i = 0; i < NUM_THREADS; i++) {
		void *retval = NULL;
		if (ft_pthread_join(&threads[i], &retval) != 0) {
			fprintf(stderr, "Error joining thread %d\n", i);
			continue;
		}
		/* printf("thread id after join %d\n", thread_ids[i]); */
	}
	
	free(thread_ids);
	return EXIT_SUCCESS;
}
