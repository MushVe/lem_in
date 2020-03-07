# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/26 01:31:01 by cseguier          #+#    #+#              #
#    Updated: 2020/03/07 05:54:59 by cseguier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#.PHONY: all, clean, fclean, re
# all: 
# 	@ gcc -o lem-in parser/*.c hash_table/*.c main.c libftprintf.a

NAME = lem-in #cseguier.filler

LIBFT = libft/libftprintf.a

FILE = ants.c main.c parser.c utils_parser.c room.c utils_room.c tubes.c \
	utils_tubes.c utils.c utils_2.c algo.c utils_algo.c node.c

INC = -I libft 

SRC = $(FILE:%=%)
OBJ = $(FILE:%.c=objs/%.o)

FLAG = #-fsanitize=address # -Wall -Werror -Wextra  -g3
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

objs/%.o: algo/%.c
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