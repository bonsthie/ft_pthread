#ifndef FT_PTHREAD_H
# define FT_PTHREAD_H

#include <stdatomic.h>
# include <stdint.h>
# include <pthread.h>


typedef void			*(*t_pthread_routine)(void *);

enum thread_status {
	TH_RUNNING,
	TH_JOINABLE,
};

typedef struct s_pthread_attr
{
	uint32_t			stack_size;
}						t_pthread_attr;

typedef struct s_pthread
{
	// thread settings
	int					tid;
	t_pthread_routine	routine;
	atomic_int			thread_status;
	t_pthread_attr		attr;

	// user settings

	void				*arg;
	void				*ret;
}						t_pthread;

t_pthread				*ft_pthread_self(void);

int						ft_pthread_create(t_pthread *__restrict__ thread,
							const t_pthread_attr *__restrict__ attr,
							void *(*start_routine)(void *),
							void *__restrict__ arg);


int ft_pthread_join(t_pthread *thread, void **value_ptr);

#endif /* FT_PTHREAD_H */
