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

void	init_combo(t_path_combo **path_combo, int limit)
{
	int	i;

	if (!(*path_combo = ft_memalloc(sizeof(t_path_combo) * limit + 1)))
		exit_error("Malloc Failed", (char*)__func__);
	i = -1;
	while (++i < limit)
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
	// ft_printf("NBPATH>>> %d\n", nb_path);
	while (++path_id < nb_path)
		ft_printf("Ants: %d in Path #%d of Size %d\n",
			ants_by_rooms[path_id], path_id, path_combo[path_id].size);
	

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
//	ft_printf("-> COLLIDE ");
	while (++target_room_id < bfs->path_array[target_id].size)
	{
		path_id = -1;
		while (combo[++path_id].ants != -1)
		{
			room_id = -1;
			while (++room_id < combo[path_id].size - 1)
			{
				//// ft_printf("[%d] x [%d]\n",
				//	 combo[path_id].room[room_id], bfs->path_array[target_id].room[target_room_id]);
				if (combo[path_id].room[room_id] == \
					bfs->path_array[target_id].room[target_room_id]
					&& room_id != 0)
				{
					ft_printf("-> BONK\n");
					return (1);
				}
			}
		}
	}
	ft_printf("-> SMOOTH\n");
	return (0);
}

int		find_cible(t_path_combo *path, int nb_path, int marge)
{
	int	i;
	int	cible_max;
	int	cible_min;

	i = -1;
	cible_max = -1;
	cible_min = -1;
	while (++i < nb_path)
	{
		if (path[i].ants < path[cible_max].ants)
			cible_max = i;
		if (path[i].ants > path[cible_min].ants)
			cible_min = i;
	}
	if (marge < 0)
		return (cible_max);
	return (cible_min);
}

int		adjust_ants(t_path_combo *path, int nb_path, int marge, int lines)
{
	int	i;
	int	op;
	int	cible;

	i = -1;
	if (marge < 0)
		op = 1;
	else
		op = -1;
	while (marge != 0)
	{
		cible = find_cible(path, nb_path, marge);
		path[cible].ants += op;
		marge += op;
		lines -= op;
	}
	return (lines);
}

int		lead_ants(t_path_combo *path, int ants, int nb_path)
{
	int	lines;
	int	i;
	int total_ants;

	lines = 0;
	i = -1;
	total_ants = 0;
	ft_printf("\n\t\t\t\t--- LEAD ANTS ---\n");
	while (++i < nb_path)
	{
		ft_printf("\t\t\t\tLine #%d = %d\n", i, (ants / nb_path) + path[i].size - 2);
		lines += (ants / nb_path) + path[i].size - 2;
	}
	lines = ft_round(lines, nb_path);
	i = -1;
	while (++i < nb_path)
		path[i].ants = lines - (path[i].size - 2);
	i = -1;
	while (++i < nb_path)
	{
		ft_printf("\t\t\t\to> ANTS %d for PATH #%d\n", path[i].ants, i);
		total_ants += path[i].ants;
	}
	ft_printf("\t\t\t\tTotal Ants : %d\n", total_ants);
	if (total_ants != ants)
		lines = adjust_ants(path, nb_path, total_ants - ants, lines);
	ft_printf("\t\t\t\t--- LEAD ANTS ---\n\n");
	return (lines);
}

int	get_shortest_combo(t_p *p, t_bfs *bfs, t_nb *nb, t_path_combo *path_combo)
{
	t_path_combo	*best_combo;
	int				shortest_id;
	int				best_nb_lines;
	int				best_nb_path;
	int				path_id;
	int				test_limit;
	int				test_id;
	int				minimum_size;
	int				shortest;

	//limiting factor : start and end room connections + ant number (maj malloc combo)
	//trier chemins

	test_id = -1;
	best_nb_lines = __INT_MAX__;
	best_nb_path = 0;
	nb->path = 0;
	shortest = 0;

	test_limit = get_test_limit(p);
	if (test_limit == -1)
		exit_error("Test Limit Exited", (char*)__func__);
	ft_printf("Test Limit : %d\n", test_limit);
	init_combo(&best_combo, test_limit);
	while (++test_id < bfs->path_nb)
	{
		shortest = 0;
		ft_printf("ID:%d path:%d\n", test_id, bfs->path_nb);
		shortest_id = test_id - 1;
		path_id = -1;
		nb->line = 0;
		clear_path_combo(path_combo, test_limit);
		ft_printf("\n--------------- TEST #%d ---------------\n", test_id);
		nb->path = 0;
		ft_printf("_______conditions nbpath:%d antcount:%d bfspathnb:%d\n",
			nb->path, p->data.ant_count, bfs->path_nb);
		while (++nb->path <= test_limit)
		{
			ft_printf("_______ROUND #%d > ", nb->path);
			shortest_id = get_next_path(bfs, shortest_id);
			ft_printf("got new path [%d] ", shortest_id);
			if (shortest_id == -1)
			{
				shortest = 1;
				ft_printf(" -> No More Paths\n");
				nb->path--;
				if (test_id < test_limit)
					minimum_size++;
				break;
			}
			else if (!(collide(bfs, path_combo, shortest_id)))
			{
				//nb->path++;
				copy_path(bfs, path_combo, shortest_id, ++path_id);
				ft_printf("nb_lines_before: %d, nb_path: %d\n", nb->line, nb->path);
				nb->line = lead_ants(path_combo, p->data.ant_count, nb->path);
				print_combo(p, path_combo, test_limit);
				ft_printf("nb_line %d, best %d\n", nb->line, best_nb_lines);
				if (nb->line < best_nb_lines)
				{
					best_nb_path = nb->path;
					best_nb_lines = nb->line;
					ft_printf("\tnew best %d\n", best_nb_lines);
					clear_path_combo(best_combo, test_limit);
					copy_path_combo(best_combo, path_combo, nb->path);
				}
			}
			else
			{
				// ft_printf("Is it working ?\n");
				nb->path--;
			}
			
		}
	}
	// ft_printf("\tOut of the loop\n");
	// clear_path_combo(path_combo, p->data.ant_count);
	// clear_path_combo(best_combo, p->data.ant_count);
	clear_path_combo(path_combo, test_limit);
	copy_path_combo(path_combo, best_combo, best_nb_path);
	nb->line = best_nb_lines;
	nb->path = best_nb_path;
	// ft_printf("---------- nb path out of inferno %d ----------\n", best_nb_path);
	ft_printf("---------- out of inferno paths #%d lines #%d----------\n", nb->path, nb->line);
	return (nb->path);
	// shortest_id = get_shortest_path(bfs);
	// // ft_printf("\nshortest: #%d of %d rooms for %d ants\n", \
	// 	shortest_id, bfs->path_array[shortest_id].size, p->data.ant_count);
}

int resolve(t_p *p, t_bfs *bfs)
{
	t_path_combo	*path_combo;
	t_nb			nb;
	int				test_limit;

	quicksort(bfs);
	init_combo(&path_combo, p->data.ant_count);

	test_limit = get_shortest_combo(p, bfs, &nb, path_combo);

	// ft_printf("\n++ total lines {%d} ants {%d} ++\n", nb.line, p->data.ant_count);
	print_combo(p, path_combo, test_limit);
	// ft_printf("\n");
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