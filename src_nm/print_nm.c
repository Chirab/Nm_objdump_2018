/*
** EPITECH PROJECT, 2019
** print_nm.c
** File description:
** print_nm
*/

#include "../include/my.h"

char choose_flag(nm_t *nm, size_t i)
{
    nm->c = '?';
    if (nm->shdr[nm->sym[i].st_shndx].sh_flags == (SHF_EXECINSTR | SHF_ALLOC))
        nm->c = 'T';
    if (ELF64_ST_BIND(nm->sym[i].st_info) == STB_GNU_UNIQUE)
        nm->c = 'u';
    if (ELF64_ST_BIND(nm->sym[i].st_info) == STB_WEAK
        && ELF64_ST_TYPE(nm->sym[i].st_info) == STT_OBJECT)
        nm->c = (nm->sym[i].st_shndx == SHN_UNDEF) ? 'v' : 'V';
    else if (ELF64_ST_BIND(nm->sym[i].st_info) == STB_WEAK)
        nm->c = (nm->sym[i].st_shndx == SHN_UNDEF) ? 'w' : 'W';
    else if (nm->sym[i].st_shndx == SHN_UNDEF)
        nm->c = 'U';
    else if (nm->sym[i].st_shndx == SHN_ABS)
        nm->c = 'A';
    else if (nm->sym[i].st_shndx == SHN_COMMON)
        nm->c = 'C';
    if (ELF64_ST_BIND(nm->sym[i].st_info) == STB_LOCAL && nm->c != '?')
        nm->c += 32;
    return (nm->c);
}

void compare(nm_t *nm, int i)
{
    if (nm->shdr[i].sh_size) {
        if (strcmp(&nm->str[nm->shdr[i].sh_name], ".symtab") == 0)
            nm->symtab = (Elf64_Shdr *) &nm->shdr[i];
        if (strcmp(&nm->str[nm->shdr[i].sh_name], ".strtab") == 0)
            nm->strtab = (Elf64_Shdr *) &nm->shdr[i];
    }
}

void init_nm(nm_t *nm, char *data)
{
    nm->sym = ((void *)data + nm->symtab->sh_offset);
    nm->str = (char *) ((void *)data +  nm->strtab->sh_offset);
    nm->datab = malloc(sizeof(char *));
}

void print_nm1(nm_t *nm)
{
    char c;

    for (size_t i = 0; i < (nm->symtab->sh_size
                            / nm->symtab->sh_entsize); i++) {
        if ((strlen(&nm->str[nm->sym[i].st_name]) != 0)
            && (strstr(&nm->str[nm->sym[i].st_name], ".c") == NULL)) {
            c =  choose_flag(nm, i);
            if (c == 'U' || c == 'W')
                printf("                 %c %s\n",
                       c, &nm->str[nm->sym[i].st_name]);
            else
                printf("%016lx %c %s\n",
                       nm->sym[i].st_value, c, &nm->str[nm->sym[i].st_name]);
        }
    }
}

void print_nm(Elf64_Ehdr *elf, char *data)
{
    nm_t *nm = malloc(sizeof(nm) + 100);
    nm->shdr = (Elf64_Shdr *) ((void *)data + elf->e_shoff);
    nm->str = (char *) ((void *)data + nm->shdr[elf->e_shstrndx].sh_offset);

    for (int i = 0; i < elf->e_shnum; i++)
        compare(nm, i);
    init_nm(nm, data);
    print_nm1(nm);
}
