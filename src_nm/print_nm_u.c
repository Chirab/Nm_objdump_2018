/*
** EPITECH PROJECT, 2019
** print_nm_u
** File description:
** print_nm_u
*/

#include "../include/my.h"

void nm_u(nm_t *nm)
{
    char c;

    for (size_t i = 0; i < (nm->symtab->sh_size
                            / nm->symtab->sh_entsize); i++) {
        if ((strlen(&nm->str[nm->sym[i].st_name]) != 0)
            && (strstr(&nm->str[nm->sym[i].st_name], ".c") == NULL)) {
            c =  choose_flag(nm, i);
            if (c == 'U' || c == 'w') {
                printf("                 %c %s\n", c, &nm->str[nm->sym[i].st_name]);
            }
        }
    }
}

void print_nm_u(Elf64_Ehdr *elf, char *data)
{
    nm_t *nm = malloc(sizeof(nm) + 100000);
    nm->shdr = (Elf64_Shdr *) ((void *)data + elf->e_shoff);
    nm->str = (char *) ((void *)data + nm->shdr[elf->e_shstrndx].sh_offset);

    for (int i = 0; i < elf->e_shnum; i = i + 1)
        compare(nm, i);
    init_nm(nm, data);
    nm_u(nm);
}
