#include "readelf.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define STT_GNU_IFUNC 10

// dummy verison of dlsym that look for a symbol in the .dynsym

#ifdef VERBOSE
#define LOG(format, ...) printf(format, __VA_ARGS__)
#else
#define LOG(format, ...)
#endif

typedef void *(*ifunc_func)(void);

Elf64_Shdr	*find_dlsym_header_offset(Elf64_Shdr *shdr, uint16_t nb_shdr,
		const char *shstrtab)
{
	while (nb_shdr--)
	{
		LOG("-- Section size: 0x%lx -- Remaining sections: %d -- ",
			shdr->sh_size, nb_shdr);
		LOG("Section name: '%s'\n", shstrtab + shdr->sh_name);
		if (shdr->sh_type == SHT_DYNSYM && !strcmp(shstrtab + shdr->sh_name, ".dynsym"))
		{
			printf(".dynsym find at %p\n", shdr);
			return (shdr);
		}
		shdr++;
	}
	return (0);
}

Elf64_Shdr	*find_symbol_string_table_offset(Elf64_Shdr *shdr, uint16_t nb_shdr, const char *shstrtab)
{
	while (nb_shdr--)
	{
		if (shdr->sh_type == SHT_STRTAB && !strcmp(shstrtab + shdr->sh_name, ".dynstr"))
		{
			printf(".dynstr find at %p\n", shdr);
			return (shdr);
		}
		shdr++;
	}
	return (0);
}

Elf64_Sym *shdr_to_simbol(void *handle, Elf64_Shdr *sym_hdr, Elf64_Shdr *sym_string, const char *symbol)
{
	Elf64_Sym *sym;
	uint16_t	nb_sym;
	const char *sym_str;

	sym = handle + sym_hdr->sh_offset;
	nb_sym = sym_hdr->sh_size / sizeof(Elf64_Sym);
	sym_str = handle + sym_string->sh_offset;


	void *result = NULL;
	while (nb_sym--)
	{
		LOG("%d %p symbol : %s\n", nb_sym, handle + sym->st_value, sym_str + sym->st_name);
		if (!strcmp(sym_str + sym->st_name, symbol))
		{
			printf("symbol %s found at %p\n", symbol, sym);
			result = sym;
		}
		sym++;
	}
	return (result);
	(void)symbol;


}

Elf64_Sym *find_symbol(void *handle, Elf64_Shdr *shdr, uint16_t nb_shdr, const char *shstrtab, const char *symbol)
{
	Elf64_Shdr *sym_hdr = find_dlsym_header_offset(shdr, nb_shdr, shstrtab);
	if (!sym_hdr)
		return (NULL);
	Elf64_Shdr *sym_string_hdr = find_symbol_string_table_offset(shdr, nb_shdr, shstrtab);
	if (!sym_string_hdr)
		return (NULL);
	return (shdr_to_simbol(handle, sym_hdr, sym_string_hdr, symbol));
}

void	*ft_dlsym(void *handle, const char *symbol)
{
	Elf64_Ehdr	*elf_header;
	Elf64_Shdr	*shdr;
	Elf64_Shdr	*shstrtab_hdr;
	char		*shstrtab;

	elf_header = handle;
	shdr = (Elf64_Shdr *)(handle + elf_header->e_shoff);
	shstrtab_hdr = &shdr[elf_header->e_shstrndx];
	shstrtab = (char *)(handle + shstrtab_hdr->sh_offset);

	Elf64_Sym *sym = find_symbol(handle, shdr, elf_header->e_shnum, shstrtab, symbol);
	if (!sym)
		return (NULL);
	printf("%s is at offset %lx that point to address %p\n", symbol, sym->st_value, handle + sym->st_value);
	if ((sym->st_info & 0xf) == STT_GNU_IFUNC)
	{
		printf("is ifunc\n");
		void *resolver_address = (char *)handle + sym->st_value;
		ifunc_func ifunc_resolver = (ifunc_func)resolver_address;
		void *ret = ifunc_resolver();
		printf("ifunc addres %p\n", ret);
		return (ret);
	}
	else 
		printf("is not ifunc\n");
	return (handle + sym->st_value);
}
