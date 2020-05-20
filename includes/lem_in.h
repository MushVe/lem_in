/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 01:37:37 by cseguier          #+#    #+#             */
/*   Updated: 2020/05/20 16:56:58 by cseguier         ###   ########.fr       */
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
	t_map_room_index	*junction;
	int					**matrix;
	t_anthill			data;
	t_list				*tmp;
	t_hthandle			hthandler;
}					t_p;

typedef struct		s_path_list
{
	int					*room;
	int					size;
	struct s_path_list	*next;
}					t_path_list;

typedef struct		s_path_array
{
	int	*room;
	int	size;
}					t_path_array;

typedef struct		s_room_status
{
	int	id;
	int	ant;
}					t_room_status;

typedef struct		s_path_combo
{
	t_room_status	*room;
	int				size;
	int				ants;
}					t_path_combo;

typedef struct		s_combo_data
{
	t_path_combo	*path_combo;
	int				nb_path;
	int				nb_line;

}					t_combo_data;

typedef struct		s_bada_ids
{
	int	path;
	int	room;
	int	ant;
}					t_bada_ids;

typedef struct		s_ant_status
{
	int	id_path;
	int	id_room;
}					t_ant_status;

typedef struct		s_combo_utils
{
	t_path_combo	*best_combo;
	int				first_path;
	int				best_nb_lines;
	int				best_nb_path;
	int				path_id;
	int				test_limit;
	int				test_id;
	int				minimum_size;
	int				best_behind;
	int				nb_total_ants;
}					t_combo_utils;

typedef struct		s_room_infos
{
	int				distance_start;
	int				distance_end;
	int				score;
	int				token;
	int				nb_link;
	int				current_link;
	int				*link_array;
}					t_room_infos;

typedef struct		s_bfs
{
	int				final_score;
	int				*matrix_level;
	int				*visited_record;
	int				*parent;
	t_path_list		*path_list;
	int				*tmp_path;
	int				max_path;
	int				path_id;
	int				path_nb;
	int				real_path_nb;
	int				host;
	int				link;
	t_path_array	*path_array;
	t_room_infos	*rooms;
}					t_bfs;

/*
** Print
*/

int					print_lem_in(t_p *p, t_combo_data *cd);
void				go_to_next(t_combo_data *c, t_ant_status *a, t_bada_ids i);

/*
** Algo
*/

int					algo(t_p *p, t_bfs *bfs);
void				bfs_free_list(t_path_list **path);
int					bfs_new_node(int *data, t_path_list **path, int size);
int					*bfs_get_node(int aim, t_path_list *path);
void				bfs_init(t_bfs *bfs, int size);
void				fill_path_array(t_bfs *bfs);
void				print_path_array(t_p *p, t_bfs *bfs);
void				print_matrix(t_p *p, t_bfs *bfs, int i, int j);
void				get_matrix_level(t_p *p, t_bfs *bfs);
void				bfs_free_all(t_bfs *bfs);
void				reset_visited(t_p *p, t_bfs *bfs);

/*
** Algo dfs
*/

void				dfs_solve(t_p *p, t_bfs *bfs);
int					is_closer(int *d_start, int *d_end, int way, t_room_infos current);
int					find_best_room(t_room_infos *rooms, int host, int way);
void				get_ultimate_result(t_p *p, t_bfs *bfs);
void				set_nb_link(t_p *p, t_bfs *bfs);
void				remove_bad_link(t_bfs *bfs, t_p *p);
int					create_path(t_p *p, t_bfs *bfs);
void				reorder_path(t_bfs *bfs);
void				dfs_solve(t_p *p, t_bfs *bfs);
int					find_n_kill_dopples(int	path_nb, t_path_array *path_array);
t_path_array		*clean_path_array(t_path_array *path_array, int path_nb, int real_path_nb);
void				save_path(t_p *p, t_bfs *bfs, int index, int size);
void				ignore_path(t_path_array *path_array, int i_other_path);
int					is_the_same(t_path_array *path_array, int i_current_path, int i_other_path);

/*
** Resolve
*/

t_path_combo		*resolve(t_p *p, t_bfs *bfs, t_combo_data *cd);
void				copy_path(t_bfs *b, t_path_combo *p, int pi, int ci);
void				copy_path_combo(t_path_combo *f, t_path_combo *p, int l);
void				print_combo(t_p *p, t_combo_data *cd);
void				quicksort(t_bfs *bfs);
int					get_test_limit(t_p *p);
void				init_combo(t_path_combo **path_combo, int limit);
void				clear_path_combo(t_path_combo *path_combo, int ant);
int					collide(t_bfs *bfs, t_path_combo *combo, int target_id);
void				get_start_values(t_combo_data *cd, t_combo_utils *u);
int					lead_ants(t_path_combo *path, int ants, int nb_path);
void				init_utils(t_p *p, t_combo_data *cd, t_combo_utils *u);
void				free_path_combo(t_path_combo *combo, int nb_path);

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
void			print_path_list(t_p *p, t_bfs *bfs);
void			print_path_array(t_p *p, t_bfs *bfs);

/*
** Ants
*/

void				handle_ants(t_p *p);

/*
** Rooms
*/

int					is_room(char *line);
int					is_room_valid(char *line);
int					got_start_end(int command_flag, t_anthill *data);
void				assign_command(t_anthill *data, char *command, char *line);
int					handle_rooms(char **l, t_list **t, t_anthill *d);
int					white_space_count(char *line);
int					is_room(char *line);
int					is_room_name_alphanumerical(char *line);
int					is_coord_only_digit(char *line);
int					is_tube(char *line);
int					is_coord_valid(char *line);

/*
** Tubes
*/

t_ht				*does_room_exist(char *line, t_hthandle *t_hthandler);
int					is_tube_valid(t_ht **a, t_ht **b, char *l, t_hthandle *ht);
char				*split_tubes(char *line);
int					handle_tubes(t_p *p, char **c);

/*
** parser
*/

int					parser(t_p *p);
void				display(t_anthill data, t_list *list);
void				delete_junction_table(t_map_room_index *junction);
void				delete_display_list(t_list *list);
t_list				*create_node(char *data);
int					add_front_node(t_list **head, char *data);
t_map_room_index	*store_rooms(t_anthill *d, t_hthandle *ht, t_list *r);

#endif
