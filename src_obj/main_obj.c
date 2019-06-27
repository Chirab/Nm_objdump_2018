/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main_obj
*/

#include "../include/my.h"

int objdump(char *str, char *file)
{
    if (file == NULL)
        return (84);
    if (check_elf_file(file) == 0) {
        if (check_format() == 0)
            bit64(str);
        else
            bit32(str);
    }
    else {
        printf("nm: %s File format not recognized\n", str);
        return (84);
    }
    return (0);
}

char *check_file(char *file)
{
    int fd;
    struct stat s;
    char *buf;

    fd = open(file, O_RDONLY);
    if (fd == -1) {
        perror(file);
        return (NULL);
    }
    fstat(fd, &s);
    buf = mmap(NULL, s.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (buf == NULL)
        return (NULL);
    close(fd);
    return (buf);
}

int main(int ac, char **av)
{
    char *str;
    int a = 1;

    if (ac == 1)
        show_help();
    else
        if (ac > 1) {
            for (; av[a] != NULL; a++) {
                str = check_file(av[a]);
                objdump(av[a], str);
            }
        }
    return (0);
}
