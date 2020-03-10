/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_resolve.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 15:59:09 by cseguier          #+#    #+#             */
/*   Updated: 2020/03/10 18:10:54 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int	get_shortest_path(t_bfs *bfs)
{
	int	path_id;
	int	shortest;
	int	res;

	path_id = -1;
	shortest = __INT_MAX__;
	while (++path_id < bfs->path_nb)
	{
		if (bfs->path_array[path_id].size < shortest)
		{
			shortest = bfs->path_array[path_id].size;
			res = path_id;
		}
	}
	return (res);
}

void	copy_path(t_bfs *bfs, t_path_combo *path_combo, int path_id, int combo_id)
{
	int	room_id;

	// ft_printf("++ copy_path array into combo ++\n");
	// ft_printf("path_id: %d  combo_id: %d\n", path_id, combo_id);
	path_combo[combo_id].size = bfs->path_array[path_id].size;
	if (!(path_combo[combo_id].room = ft_memalloc(sizeof(int) * bfs->path_array[path_id].size)))
		exit_error("Malloc Failed", (char*)__func__);
	room_id = -1;
	while (++room_id < bfs->path_array[path_id].size)
	{
		// ft_printf("room_id: %d ", room_id);
		// ft_printf("[%d] ", bfs->path_array[path_id].room[room_id]);
		// ft_printf("[%d]\n", path_combo[combo_id].room[room_id]);
		path_combo[combo_id].room[room_id] = bfs->path_array[path_id].room[room_id];
	}
}

void	copy_path_combo(t_path_combo *final, t_path_combo *path)
{
	int	path_id;
	int	room_id;

	path_id = -1;
	while (path[++path_id].ants != -1)
	{
		final[path_id].ants = path[path_id].ants;
		final[path_id].size = path[path_id].size;
		if (!(final[path_id].room = ft_memalloc(sizeof(int) * final[path_id].size)))
			exit_error("Malloc Failed", (char*)__func__);
		room_id = -1;
		while (++room_id < path[path_id].size)
			final[path_id].room[room_id] = path[path_id].room[room_id];
	}
}

void	print_combo(t_p *p, t_path_combo *path)
{
	int	path_id;
	int	room_id;

	path_id = -1;
	while (path[++path_id].ants != -1)
	{
		ft_printf("Ants: %d ", path[path_id].ants);
		ft_printf("Path Size: %d\n", path[path_id].size);
		room_id = -1;
		while (++room_id < path[path_id].size)
		{
			if (room_id != 0)
				ft_printf(" - ");
			ft_printf("[%s]", p->junction[path[path_id].room[room_id]].room_name);
		}
		ft_printf("\n");
	}
	
}
