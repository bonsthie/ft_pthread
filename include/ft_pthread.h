#ifndef FT_PTHREAD_H
# define FT_PTHREAD_H

# include <stdint.h>

typedef void			*(*t_pthread_routine)(void *);

typedef struct s_pthread_attr
{
	uint32_t			stack_size;
}						t_pthread_attr;

typedef struct s_pthread
{
	t_pthread_attr		attr;
	t_pthread_routine	routine;
	void				*arg;
}						t_pthread;

t_pthread				*ft_pthread_self(void);

int						ft_pthread_create(t_pthread *__restrict__ thread,
							const t_pthread_attr *__restrict__ attr,
							void *(*start_routine)(void *),
							void *__restrict__ arg);

int ft_printf(const char *format, ...);
void *ft_dlsym(void *handle, const char *symbol);

#endif /* FT_PTHREAD_H */
