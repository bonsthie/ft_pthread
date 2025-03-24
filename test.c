#define _GNU_SOURCE

#include "include/ft_pthread.h"
#include "src/ft_pthread_log.h"
#include <stdio.h>
#include <stdlib.h>

#include <sys/auxv.h>
#include <stdlib.h>

#include <unistd.h>

/* __thread int ok = -1; */

void *__thread_routine(void *data)
{
	(void)write(1, "test\n", 5);
	/* __ft_pthread_log_self("start routine"); */
	/* int res; */
	/* sleep(100); */
	/* res = 0; */
	/* for (int i = *(int *)data; i < 10000010; i++) */
	/* { */
	/*   if (i % 1000000 == 0) */
	/* 	{ */
	/* 		__ft_pthread_log_self("routine going i == %d", i); */
	/* 		sleep(1); */
	/* 	} */
	/* 	res += i; */
	/* } */

	(void)data;
	__ft_pthread_log_self("end routine");
	return (void *)(uintptr_t)0;
}

void *thread_routine(void *arg) {
    int id = *((int *)arg);
    
	ft_tsprintf("Thread[%d]: Hello World!\n", id);
	/* t_pthread *self = ft_pthread_self(); */

	/* ft_tsprintf("thread value %d\n", ok); */
	/* ok++; */

    // Allocate memory for the result
    int *result = malloc(sizeof(int));
    if (!result) {
        fprintf(stderr, "Failed to allocate memory in thread %d\n", id);
        return NULL;
    }
	fprintf(stdout, "What %p (%p)\n", thread_routine, result);
    
    // For example, add 10 to the id (you can change the computation as needed)
    *result = id + 10;
    
    // Return the pointer to the result
    return 0;
}

int main(void) {


	const int NUM_THREADS = 5;
	t_pthread threads[NUM_THREADS];
	//int thread_ids[NUM_THREADS];
	
	// Allocate an array to hold the thread id values.
	int *thread_ids = malloc(NUM_THREADS * sizeof(int));
	if (!thread_ids) {
		fprintf(stderr, "Failed to allocate memory for thread IDs\n");
		return EXIT_FAILURE;
	}
	/* ft_tsprintf("thread value %d\n", ok); */
	/* ok++; */
	
	// Create 10 threads.
	for (int i = 0; i < NUM_THREADS; i++) {
		thread_ids[i] = i;
		ft_tsprintf("create thread %d\n", i);
		if (ft_pthread_create(&threads[i], NULL, thread_routine, &thread_ids[i]) != 0) {
			fprintf(stderr, "Error creating thread %d\n", i);
			free(thread_ids);
			return EXIT_FAILURE;
		}
		ft_tsprintf("end create thread %d\n", i);

	}
	
	// Join each thread and print its result.
	for (int i = 0; i < NUM_THREADS; i++) {
		void *retval = NULL;
		if (ft_pthread_join(&threads[i], &retval) != 0) {
			fprintf(stderr, "Error joining thread %d\n", i);
			continue;
		}
		if (retval) {
			int result = *((int *)retval);
			printf("Thread %d returned: %d\n", i, result);
			free(retval);
		}
	}
	
	free(thread_ids);
	return EXIT_SUCCESS;
}
