#ifndef FT_PTHREAD_H
#define FT_PTHREAD_H


typedef struct s_pthread
{

} t_pthread;

typedef struct s_pthread_attr
{

} t_pthread_attr;


 int ft_pthread_create(t_pthread *__restrict__ thread,
                          const t_pthread_attr *__restrict__ attr,
                          void *(*start_routine)(void *),
                          void *__restrict__ arg);

#endif /* FT_PTHREAD_H */
