# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/26 01:31:01 by cseguier          #+#    #+#              #
#    Updated: 2020/05/20 19:35:57 by cseguier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re
.SILENT:

NAME = lem-in

LIBFT = libft/libftprintf.a

FILE = ants.c main.c parser.c utils_parser.c room.c utils_room.c tubes.c \
	utils_tubes.c utils.c utils_2.c algo.c utils_algo.c node.c \
	resolve.c utils_resolve.c quicksort.c print.c utils_print.c \
	resolve_tools.c resolve_utils2.c dfs_path_utils.c dfs_path.c \
	dfs_utils.c dfs.c

INC = -I libft
SRC = $(FILE:%=%)
OBJ = $(FILE:%.c=objs/%.o)
CFLAGS = -fsanitize=address,undefined #-Wall -Werror -Wextra  -g3 #-O3#
CC = gcc $(CFLAGS) $(INC)
RM = rm -rf

all: $(NAME)

$(NAME) : $(LIBFT) $(OBJ)
	$(CC) -o $@ $(OBJ) -L libft/ -lftprintf 

$(LIBFT) : FORCE
	make -C libft/ all

FORCE:

objs/%.o: src/%.c
	mkdir -p objs
	$(CC) $(INC) -o $@ -c $<

objs/%.o: src/*/%.c
	mkdir -p objs
	$(CC) $(INC) -o $@ -c $<

clean:
	$(RM) $(OBJ)
	rm -rf objs
	make -C libft/ clean

fclean: clean
	$(RM) $(NAME)
	make -C libft/ fclean

re: fclean
	$(MAKE)
