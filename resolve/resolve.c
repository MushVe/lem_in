/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 09:46:07 by cseguier          #+#    #+#             */
/*   Updated: 2020/03/12 18:43:30 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"
#include <stdio.h>

void	init_combo(t_path_combo **path_combo, int ant)
{
	int	i;

	if (!(*path_combo = ft_memalloc(sizeof(t_path_combo) * ant + 1)))
		exit_error("Malloc Failed", (char*)__func__);
	i = -1;
	while (++i < ant)
	{
		(*path_combo)[i].size = -1;
		(*path_combo)[i].ants = -1;
		(*path_combo)[i].room = NULL;
	}
}

void	fill_ants_by_rooms(int **ants, t_path_combo *path, int nb_path)
{
	int	path_id;

	path_id = -1;
	if (!(*ants = ft_memalloc(sizeof(int) * nb_path)))
		exit_error("Malloc Failed", (char*)__func__);
	while (++path_id < nb_path)
		(*ants)[path_id] = path[path_id].ants;
}

void	print_result(t_p *p, t_path_array *path_array, t_path_combo *path_combo, int lines, int nb_path)
{
	int	lines_id;
	int	path_id;
	int	ant_cpt;
	int	*ants_by_rooms;

	fill_ants_by_rooms(&ants_by_rooms, path_combo, nb_path);

	path_id = -1;
	ft_printf("NBPATH>>> %d\n", nb_path);
	while (++path_id < nb_path)
		ft_printf("Ants: %d in Room #%d\n", ants_by_rooms[path_id], path_id);
	

	// path_id = -1;
	// while (++path_id < nb_path)
	// {
	// 	while (path_combo[path_id].ants)
	// 	{
			
	// 	}
	// }



		ft_printf("\n");


}

void	clear_path_combo(t_path_combo *path_combo, int ant)
{
	int	i;

	i = -1;
	while (++i < ant)
	{
		path_combo[i].ants = -1;
		path_combo[i].size = -1;
		if (path_combo[i].room)
			ft_memdel((void*)&path_combo[i].room);
	}
}

int	collide(t_bfs *bfs, t_path_combo *combo, int target_id)
{
	int	path_id;
	int	room_id;
	int	target_room_id;

	target_room_id = -1;
	while (++target_room_id < bfs->path_array[target_id].size)
	{
		path_id = -1;
		while (combo[++path_id].ants != -1)
		{
			room_id = -1;
			while (++room_id < combo[path_id].size)
			{
				if (combo[path_id].room[room_id] == \
					bfs->path_array[target_id].room[target_room_id])
				{
					return (1);
				}
			}
		}
	}
	return (0);
}

int		lead_ants(t_path_combo *path, int ants, int nb_path)
{
	int	lines;
	int	i;

	lines = 0;
	i = -1;

	while (++i < nb_path)
	{
		ft_printf("Line #%d = %d\n", i, (ants / nb_path) + path[i].size - 2);
		lines += (ants / nb_path) + path[i].size - 2;
	}
	ft_printf("after line: %d\n", lines);
	lines = ft_round(lines, nb_path);
	ft_printf("final lines: %d\n", lines);
	i = -1;
	while (++i < nb_path)
		path[i].ants = lines - (path[i].size - 2);
	i = -1;
	while (++i < nb_path)
		ft_printf("o> ANTS %d for ROOM #%d\n", path[i].ants, i);
	return (lines);
}

int	get_shortest_combo(t_p *p, t_bfs *bfs, t_nb *nb, t_path_combo *path_combo)
{
	t_path_combo	*best_combo;
	int				shortest_id;
	int				best_nb_lines;
	int				path_id;
	int				test_limit;
	int				test_id;
	int				minimum_size;
	int				shortest;

	shortest = 0;
	shortest_id = -1;
	test_limit = 2;
	test_id = -1;
	best_nb_lines = __INT_MAX__;
	minimum_size = -1;
	nb->path = 0;
	init_combo(&best_combo, p->data.ant_count);
	while (shortest != 1 && ++test_id < test_limit)
	{
		path_id = -1;
		nb->line = 0;
		ft_putnbr(test_id);
		ft_printf("\t ---- test id %d\n", test_id);
		ft_printf("\n--------------- TEST #%d ---------------\n", test_id);
		nb->path = 0;
		while (++nb->path < p->data.ant_count && nb->path < bfs->path_nb)
		{
			ft_printf("_______ROUND #%d > ", nb->path);
			shortest_id = get_next_shortest_path(bfs, shortest_id, &minimum_size);
			ft_printf("got [%d]\n", shortest_id);
			if (shortest_id == -1)
			{
				shortest = 1;
				ft_printf("Already shortest\n");
				nb->path--;
				if (test_id < test_limit)
					minimum_size++;
			}
			else if (!(collide(bfs, path_combo, shortest_id)))
			{
				//nb->path++;
				copy_path(bfs, path_combo, shortest_id, ++path_id);
				print_combo(p, path_combo);
				ft_printf("nb_lines_before: %d, nb_path: %d\n", nb->line, nb->path);
				nb->line = lead_ants(path_combo, p->data.ant_count, nb->path);
				ft_printf("nb_line %d, best %d\n", nb->line, best_nb_lines);
				if (nb->line < best_nb_lines)
				{
					best_nb_lines = nb->line;
					ft_printf("\tnew best %d\n", best_nb_lines);
					ft_printf("111\n");
					clear_path_combo(best_combo, p->data.ant_count);
					ft_printf("222\n");
					copy_path_combo(best_combo, path_combo);
					ft_printf("333\n");
					clear_path_combo(path_combo, p->data.ant_count);
					ft_printf("444\n");
				}
			}
		}
		ft_printf("\tAAAAAAAAAAAAAAAAAAAAAA\n");
		ft_printf("\tnb_line %d\n", nb->line);
	}
	ft_printf("\tOut of the loop\n");
	clear_path_combo(path_combo, p->data.ant_count);
	ft_printf("000\n");
	copy_path_combo(path_combo, best_combo);
	clear_path_combo(best_combo, p->data.ant_count);
	ft_printf("---------- nb path out of inferno %d ----------\n", nb->path);
	return (nb->path);
	// shortest_id = get_shortest_path(bfs);
	// ft_printf("\nshortest: #%d of %d rooms for %d ants\n", \
	// 	shortest_id, bfs->path_array[shortest_id].size, p->data.ant_count);
}

int resolve(t_p *p, t_bfs *bfs)
{
	t_path_combo	*path_combo;
	t_nb			nb;

	init_combo(&path_combo, p->data.ant_count);

	nb.path = get_shortest_combo(p, bfs, &nb, path_combo);

	ft_printf("\n++ total lines {%d} ants {%d} ++\n", nb.line, p->data.ant_count);
	print_combo(p, path_combo);
	ft_printf("\n");
	print_result(p, bfs->path_array, path_combo, nb.line, nb.path);
	return (0);
}


	// copy_path(bfs, path_combo, 0, 0);
	// copy_path(bfs, path_combo, 1, 1);
	// copy_path(bfs, path_combo, shortest_id, 2);
	// nb_path = 3;

//	copy_path(bfs, path_combo, shortest_id, 0);
//	nb_path = 1;


	// get short paths (increasing) no-collinding
	// get nb_line for each combo
	// keep smallest nb_line as valid w/ best_combo
	// clear path_combo and try another
	// arbitrary number of tries
	// path number in combo limited by ants number
	// should be good