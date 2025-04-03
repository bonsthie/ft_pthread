#ifndef FT_PTHREAD_ATTR_H
#define FT_PTHREAD_ATTR_H

#if !defined(FT_PTHREAD_H) && !defined(__FT_PTHREAD_ATTR_H)
#    warning ("[internal/ft_pthread_attr.h] this file should not be include directly")
#endif

// this is a tmp version for the dev of this lib the sizeof need to be replace by the hard coded
// version of the value and put the struct in the inside of the internal to completely hide the
// definition

#include <stdint.h>

struct __pthread_attr {
    uint32_t stack_size;
};

#define __FT_PTHREAD_ATTR_SIZE sizeof(struct __pthread_attr)

#endif /* FT_PTHREAD_ATTR_H */
