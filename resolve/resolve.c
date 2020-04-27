/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 09:46:07 by cseguier          #+#    #+#             */
/*   Updated: 2020/04/24 18:39:52 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

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
			while (++room_id < combo[path_id].size - 1)
			{
				if (combo[path_id].room[room_id].id == \
					bfs->path_array[target_id].room[target_room_id]
					&& room_id != 0)
					return (1);
			}
		}
	}
	return (0);
}

int		negative_ants(t_path_combo *path, int nb_path)
{
	int	i;

	i = -1;
	while (++i < nb_path)
	{
		if (path[i].ants < 0)
			return (1);
	}
	return (0);
}

int		find_cible(t_path_combo *path, int nb_path, int marge)
{
	int	i;
	int	cible_max;
	int	cible_min;

	i = -1;
	cible_max = 0;
	cible_min = 0;
	while (++i < nb_path)
	{
		if (path[i].ants + path[i].size < path[cible_max].ants + path[cible_max].size)
			cible_max = i;
		if (path[i].ants + path[i].size > path[cible_min].ants + path[cible_min].size)
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
	op = (marge < 0) ? 1 : -1;
	while (marge != 0)
	{
		cible = find_cible(path, nb_path, marge);
		path[cible].ants += op;
		marge += op;
		if (path[cible].ants + path[cible].size - 2 != lines)
			lines +=op;
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
	while (++i < nb_path)
		lines += (ants / nb_path) + path[i].size - 2;
	lines = ft_round(lines, nb_path);
	i = -1;
	while (++i < nb_path)
		path[i].ants = lines - (path[i].size - 2);
	i = -1;
	while (++i < nb_path)
		total_ants += path[i].ants;	
	if (total_ants != ants)
		lines = adjust_ants(path, nb_path, total_ants - ants, lines);
	return (lines);
}

void	free_path_combo(t_path_combo *combo, int nb_path)
{
	int	i;

	i = -1;
	while (++i < nb_path)
		ft_memdel((void*)&combo[i].room);
	ft_memdel((void*)&combo);
}

int	get_shortest_combo(t_p *p, t_bfs *bfs, t_combo_data *cd)
{
	t_path_combo	*best_combo;
	int				first_path;
	int				best_nb_lines;
	int				best_nb_path;
	int				path_id;
	int				test_limit;
	int				test_id;
	int				minimum_size;
	int				shortest;
	int				got_first;
	int				best_behind;

	test_id = -1;
	best_nb_lines = __INT_MAX__;
	best_nb_path = 0;
	cd->nb_path = 0;
	shortest = 0;
	got_first = 0;
	test_limit = get_test_limit(p);
	if (test_limit == -1)
		exit_error("Test Limit Exited", (char*)__func__);	
	init_combo(&best_combo, test_limit);
	while (++test_id < bfs->path_nb)
	{
		best_behind = 0;
		shortest = 0;
		first_path = test_id - 1;
		path_id = -1;
		cd->nb_line = 0;
		clear_path_combo(cd->path_combo, test_limit);
		cd->nb_path = 0;
		while (++cd->nb_path <= test_limit && !best_behind)
		{
			first_path = get_next_path(bfs, first_path);
			if (first_path == -1)
			{
				shortest = 1;
				cd->nb_path--;
				if (test_id < test_limit)
					minimum_size++;
				break;
			}
			else if (!(collide(bfs, cd->path_combo, first_path)))
			{
				if (bfs->path_array[first_path].size > best_nb_lines)
					best_behind = 1;
				copy_path(bfs, cd->path_combo, first_path, ++path_id);
				cd->nb_line = lead_ants(cd->path_combo, p->data.ant_count, cd->nb_path);
				if (cd->nb_line < best_nb_lines)
				{
					best_nb_path = cd->nb_path;
					best_nb_lines = cd->nb_line;
					clear_path_combo(best_combo, test_limit);
					copy_path_combo(best_combo, cd->path_combo, cd->nb_path);
				}
			}
			else
			{
				cd->nb_path--;
			}
		}
	}
	clear_path_combo(cd->path_combo, test_limit);
	copy_path_combo(cd->path_combo, best_combo, best_nb_path);
	free_path_combo(best_combo, best_nb_path);
	cd->nb_line = best_nb_lines;
	cd->nb_path = best_nb_path;
	return (0);
}

t_path_combo *resolve(t_p *p, t_bfs *bfs, t_combo_data *cd)
{
	quicksort(bfs);
	init_combo(&cd->path_combo, p->data.ant_count);
	get_shortest_combo(p, bfs, cd);
	return (0);
}
