#define _GNU_SOURCE
#include <link.h>
#include <stdio.h>
#include <string.h>

void *(*_dl_allocate_tls)(void *mem);

uintptr_t libc_base = 0;

int find_libc(struct dl_phdr_info *info, size_t size, void *data)
{
    if (strstr(info->dlpi_name, "libc.so.6"))
    {
        libc_base = info->dlpi_addr;
        strcpy((char *)data, info->dlpi_name);
        return 1;
    }
    return 0;
    (void)size;
}

int init_dl_glibc_func_ptr(const char *libc_path)
{
    void *handle = dlopen(libc_path, RTLD_NOW | RTLD_GLOBAL);

    _dl_allocate_tls = dlsym(handle, "_dl_allocate_tls");
    printf("_dl_allocate_tls %p\n", _dl_allocate_tls);

    dlclose(handle);
    return 0;
}

__attribute__((constructor)) void resolve_hidden_symbol(void)
{
    char libc_path[512] = {0};
    dl_iterate_phdr(find_libc, libc_path);

    if (!libc_base)
    {
        fprintf(stderr, "Could not find libc base address\n");
        return;
    }

    init_dl_glibc_func_ptr(libc_path);
}
