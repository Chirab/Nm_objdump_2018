/*
** EPITECH PROJECT, 2019
** file_is_correct
** File description:
** file_is_correct
*/

#include "../include/my.h"

int check_format(void)
{
    if (sizeof(void *) == 8)
        return (0);
    return (-1);
}

int check_elf_file(char *file)
{
    if (file[0] == (char)0x7f &&
        file[1] == 'E' && file[2] == 'L' && file[3] == 'F')
        return (0);
    return (-1);
}
