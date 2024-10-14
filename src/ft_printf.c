#include "sysdeps/ft_mman.h"
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <ft_pthread.h>
#include <dlfcn.h>

typedef int (*ft_vfprintf)( FILE * stream, const char * format, va_list arg );
typedef size_t (*ft_strlen)(const char *str);
typedef int (*ft_write)(int fd, const char *buf, size_t oui);

typedef int (*ft_libc_start_main)();


static long	get_file_size(int fd)
{
	long	filesize;

	filesize = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	return (filesize);
}

ft_vfprintf get_vfprintf(void *libc_base)
{
    uintptr_t libc_offset = 0x5f920;
    return (ft_vfprintf)((uintptr_t)libc_base + libc_offset);
}

void *open_libc(int *file_size)
{
	//int fd = open("/usr/lib/libc.so.6", O_RDONLY);
	int fd = open("/usr/lib/libc.so.6", O_RDONLY|O_CLOEXEC);
	if (fd == -1)
	{
		write(2, "fd\n", 3);
		return (NULL);
	}
	*file_size = get_file_size(fd);
	printf("libc size %d\n", *file_size);
	return (ft_mmap(NULL, *file_size, PROT_READ | PROT_EXEC, MAP_PRIVATE, fd, 0));
}

int ft_printf(const char *format, ...)
{
	(void)format;
	/* va_list list; */
	/* ft_vfprintf ft_vprintf_ptr; */

	int libc_size;
	void *libc  = open_libc(&libc_size);
	if (!libc)
	{
		write(2, "mmap\n", 5);
		return (0);
	}

	//ft_write ft_strlen_ptr = ft_dlsym(libc, "ft_write");
	//size_t ret = ft_strlen_ptr(1, "salut\n", 6);
	ft_strlen ft_printf_ptr = ft_dlsym(libc, "strlen");
	printf("len: %zu\n", ft_printf_ptr("salut\n"));
	int ret = 0;
	//ft_vfprintf ft_printf_ptr = dlsym(RTLD_DEFAULT, "vfprintf");
	/* va_start(list, format); */
	/* int ret = ft_printf_ptr(stdout, format, list); */
	/* va_end(list); */
	ft_munmap(libc, libc_size);
	return (ret);
}
