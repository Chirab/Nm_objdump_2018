/*
** EPITECH PROJECT, 2019
** lmy.h
** File description:
** my.h
*/

#ifndef MY_H_
#define MY_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>

/*  NM */

typedef struct nm
{
    Elf64_Shdr *shdr;
    Elf64_Shdr *symtab;
    Elf64_Shdr *strtab;
    Elf64_Sym *sym;
    char *str;
    char **datab;
    char c;
} nm_t;

char *check_file(char *file);
int construct(char *, char *);
int construct(char *, char *);
void print_nm(Elf64_Ehdr *elf, char *data);
int check_format();
int check_elf_file(char *file);
int check_diff_c(Elf64_Ehdr *format);
void init_nm(nm_t *, char *);
void print_nm1(nm_t *);
void compare(nm_t *, int);
char choose_flag(nm_t *nm, size_t i);
void print_nm_u(Elf64_Ehdr *, char *);
void nm_u(nm_t *nm);
/*  OBJDUMP */

void show_help();
int objdump(char *str, char *file);
void bit64(char *str);
void bit32(char *str);
#endif /* !MY_H_ */
