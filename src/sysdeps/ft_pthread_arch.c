#include <stdint.h>
#include <sys/cdefs.h>

#if defined(__linux__) && (__x86_64__)
uintptr_t __get_tp(void)
{
	uintptr_t	self;

	__asm__("movq %%fs:0, %0" : "=r"(self));
	return (self);
}

#elif defined(__APPLE__) && (__x86_64__)

uintptr_t __get_tp(void)
{
	uintptr_t	self;

	__asm__("movq %%gs:0, %0" : "=r"(self));
	return (self);
}
#else

# error "Unsupported platform"

#endif
