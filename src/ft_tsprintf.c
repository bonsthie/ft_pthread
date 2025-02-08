
#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>

int ft_tsprintf(const char *format, ...)
{
    static pthread_mutex_t oui;
    va_list                lst;

    va_start(lst, format);

    pthread_mutex_lock(&oui);
    int ret = vprintf(format, lst);
    pthread_mutex_unlock(&oui);

    va_end(lst);
    return ret;
}
