/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 01:37:37 by cseguier          #+#    #+#             */
/*   Updated: 2020/02/27 05:25:02 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
#define LEM_IN_H

#include "../libft/includes/hash_table.h"
#include "../libft/includes/ft_printf.h"
#include "../libft/includes/ft_get_line.h"

typedef struct	s_list
{
	char			*data;
	struct s_list	*next;
}				t_list;

	
typedef struct	s_command
{
	char	*start;
	char	*end;
}				t_command;

typedef struct	s_anthill
{
	long long	ant_count;
	long long	room_count;
	t_command	rooms;
	
}				t_anthill;

/*
** Create a mapping between
** a room and its index in
** the adjacency matrix
*/
typedef struct	s_map_room_index 
{
	int		index;
	char	*room_name;
}				t_map_room_index;


/*
** Linked list to store the anthill
*/

t_list			*create_node(char *data);
int				add_front_node(t_list **head, char *data);

/*
** Utils
*/

int				is_comment(char *line);
int				is_command(char *line);
int				is_command_valid(char *line, char **to_store);
int				is_empty(char *line);
int				**allocate_double_array(int size);
char			*allocate_room(char *line);
void			exit_error(char *reason, char *camefrom);

/*
** Ants 
*/

void			handle_ants(char **line, t_anthill *data, char **storage);

/*
** Rooms
*/

int				is_room(char *line);
int				is_room_valid(char *line);
int				got_start_end(int command_flag, t_anthill *data);
void			assign_command(t_anthill *data, char *command, char *line);
int				handle_rooms(char **line, t_list **tmp, t_anthill *data, int command_flag, char **storage);

/*
** Tubes
*/

t_ht			*does_room_exist(char *line, t_hthandle *t_hthandler);
int				is_tube_valid(t_ht **room1, t_ht **room2, char *line, t_hthandle *t_hthandler);
char			*split_tubes(char *line);
int				**handle_tubes(char **line, t_list **tubes, t_hthandle *t_hthandler, int room_count, char **stoage);


int				**parser(int *size, char **line, char **storage);

#endif