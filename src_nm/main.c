/*
** EPITECH PROJECT, 2019
** main_nm
** File description:
** main_nm
*/

#include "../include/my.h"

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
    if (fstat(fd, &s) == -1)
        return (NULL);
    buf = mmap(NULL, s.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (buf == NULL)
        return (NULL);
    close(fd);
    return (buf);
}

int construct(char *data, char *file)
{
    if (data == NULL)
        return (84);
    if (check_elf_file(data) == 0)
        print_nm((Elf64_Ehdr*)data, data);
    else {
        printf("nm: %s File format not recognized\n", file);
        return (84);
    }
    return (0);
}

int construct_u(char *data, char *file)
{
    if (data == NULL)
        return (84);
    if (check_elf_file(data) == 0)
        print_nm_u((Elf64_Ehdr*)data, data);
    else {
        printf("nm: %s File format not recognized\n", file);
        return (84);
    }
    return (0);
}

int main(int ac, char **av)
{
    char *data = NULL;

    if (ac == 1) {
        data = check_file("./a.out");
        construct(data, "./a.out");
        return (0);
    }
    if (av[1][0] == '-' && av[1][1] == 'u') {
        for (int b = 2; av[b] != NULL; b++) {
            data = check_file(av[b]);
            construct_u(data, av[b]);
        }
    }
    else
        for (int a = 1; av[a] != NULL; a++) {
            data = check_file(av[a]);
            construct(data, av[a]);
        }
    return (0);
}
