/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 01:37:37 by cseguier          #+#    #+#             */
/*   Updated: 2020/03/06 06:53:12 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/includes/hash_table.h"
# include "../libft/includes/ft_printf.h"

typedef struct		s_list
{
	char			*data;
	struct s_list	*next;
}					t_list;

typedef struct		s_command
{
	char	*start;
	int		start_index;
	int		end_index;
	char	*end;
}					t_command;

typedef struct		s_anthill
{
	long long	ant_count;
	long long	room_count;
	t_command	rooms;
}					t_anthill;

/*
** Create a mapping between
** a room and its index in
** the adjacency matrix
*/
typedef struct		s_map_room_index
{
	int		index;
	char	*room_name;
}					t_map_room_index;

typedef struct		s_p
{
	int					size;
	char				*line;
	char				*storage;
	t_map_room_index	*junction;
	int					**matrix;
	t_anthill			data;
	t_list				*tmp;
	t_hthandle			hthandler;
}					t_p;

typedef struct		s_path
{
	int				*data;
	int				size;
	struct s_path	*next;
}					t_path;

typedef struct		s_bfs
{
	int		*matrix_level;
	int		*visited_record;
	int		*parent;
	t_path	*path;
	int		*tmp_path;
	int		max_path;
	int		path_id;
}					t_bfs;

/*
** Algo
*/

int					algo(t_p *p, t_bfs *bfs);
void				bfs_free_list(t_path **path);
int					bfs_new_node(int *data, t_path **path, int size);
int					*bfs_get_node(int aim, t_path *path);

/*
** Linked list to store the anthill
*/

t_list				*create_node(char *data);
int					add_front_node(t_list **head, char *data);

/*
** Utils
*/

int					is_comment(char *line);
int					is_command(char *line);
int					is_command_valid(char *line, char **to_store);
int					is_empty(char *line);
int					**allocate_double_array(int size);
char				*allocate_room(char *line);
void				exit_error(char *reason, char *camefrom);

/*
** Ants
*/

void			handle_ants(t_p *p);

/*
** Rooms
*/

int					is_room(char *line);
int					is_room_valid(char *line);
int					got_start_end(int command_flag, t_anthill *data);
void				assign_command(t_anthill *data, char *command, char *line);
int					handle_rooms(char **l, t_list **t, t_anthill *d, char **s);
int					white_space_count(char *line);
int					is_room(char *line);
int					is_room_name_alphanumerical(char *line);
int					is_coord_only_digit(char *line);
int					is_tube(char *line);


/*
** Tubes
*/

t_ht				*does_room_exist(char *line, t_hthandle *t_hthandler);
int					is_tube_valid(t_ht **r1, t_ht **r2, char *l, t_hthandle *ht);
char				*split_tubes(char *line);
int					handle_tubes(t_p *p);
//int					**handle_tubes(char **l, t_list **t, t_hthandle *h, int r, char **s);

/*
** parser
*/

int					parser(t_p *p);
void				display(t_anthill data, t_list *list);
void				delete_junction_table(t_map_room_index *junction);
void				delete_display_list(t_list *list);
t_list				*create_node(char *data);
int					add_front_node(t_list **head, char *data);
t_map_room_index	*store_rooms(t_anthill *data, t_hthandle *ht, t_list *rooms);

#endif
