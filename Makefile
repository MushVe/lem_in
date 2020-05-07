# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cseguier <cseguier@student.42.fr>              +#+  +:+       +#+     #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/26 01:31:01 by cseguier          #+#    #+#              #
#    Updated: 2020/04/24 18:41:45 by cseguier           ###   ########.fr      #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

LIBFT = libft/libftprintf.a

FILE = ants.c main.c parser.c utils_parser.c room.c utils_room.c tubes.c \
	utils_tubes.c utils.c utils_2.c algo.c utils_algo.c node.c \
	resolve.c utils_resolve.c quicksort.c print.c utils_print.c \
	resolve_tools.c resolve_utils2.c

INC = -I libft 

SRC = $(FILE:%=%)
OBJ = $(FILE:%.c=objs/%.o)

FLAG = -Wall -Werror -Wextra #-fsanitize=address -g3
CC = gcc $(FLAG) $(INC)

RM = rm -rf

all: $(NAME)

$(NAME) : $(LIBFT) $(OBJ)
	@$(CC) -o $@ $(OBJ) -L libft/ -lftprintf 

$(LIBFT) :
	@make -C libft/ all

objs/%.o: %.c
	@mkdir -p objs
	@$(CC) $(INC) -o $@ -c $<

objs/%.o: parser/%.c
	@mkdir -p objs
	@$(CC) $(INC) -o $@ -c $<

objs/%.o: print/%.c
	@mkdir -p objs
	@$(CC) $(INC) -o $@ -c $<

objs/%.o: algo/%.c
	@mkdir -p objs
	@$(CC) $(INC) -o $@ -c $<

objs/%.o: resolve/%.c
	@mkdir -p objs
	@$(CC) $(INC) -o $@ -c $<

clean:
	@$(RM) $(OBJ)
	@rm -rf objs
	@make -C libft/ clean

fclean: clean
	@$(RM) $(NAME)
	@make -C libft/ fclean

re: fclean all

.PHONY: all clean fclean re