##
## EPITECH PROJECT, 2019
## makefile
## File description:
## makefile
##

CC      =	gcc

RM      =       rm -rf

CFLAGS	=       -Wall -Wextra

NAME    =	my_objdump

NAME1	=	my_nm

SRCSNM	= 	src_nm/main.c	\
	  	src_nm/file_is_correct.c	\
	  	src_nm/print_nm.c	\
	  	src_nm/print_nm_u.c

SRCSOBJ	=	src_obj/main_obj.c	\
		src_obj/show_help.c	\
		src_nm/file_is_correct.c	\
		src_obj/format64.c 	\
		src_obj/format32.c

OBJSNM	=       $(SRCSNM:.c=.o)

OBJS	=	$(SRCSOBJ:.c=.o)

all:		nm objdump

nm:		$(OBJSNM)
		$(CC) -o $(NAME1) $(OBJSNM) $(CFLAGS)

objdump:	$(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(CFLAGS)

clean:
		$(RM) $(OBJSNM) $(OBJS)

fclean: 	clean
		$(RM) $(NAME) $(NAME1)

re: 		fclean all

.PHONY: 	all clean fclean re nm objdump
