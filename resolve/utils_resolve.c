/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_resolve.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 15:59:09 by cseguier          #+#    #+#             */
/*   Updated: 2020/03/12 19:02:05 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int	get_next_path(t_bfs *bfs, int path_id)
{
	if (path_id + 1 < bfs->path_nb)
		return (path_id + 1);
	return (-1);
}

void	copy_path(t_bfs *bfs, t_path_combo *path_combo, int path_id, int combo_id)
{
	int	room_id;

	ft_printf("\n++ copy_path array into combo ++\n");
	ft_printf("path_id: %d  combo_id: %d  size: %d\n", path_id, combo_id, bfs->path_array[path_id].size);
	path_combo[combo_id].size = bfs->path_array[path_id].size;
	path_combo[combo_id].ants = 0;
	if (!(path_combo[combo_id].room = ft_memalloc(sizeof(int) * bfs->path_array[path_id].size)))
		exit_error("Malloc Failed", (char*)__func__);
	room_id = -1;
	while (++room_id < bfs->path_array[path_id].size)
	{
		path_combo[combo_id].room[room_id] = bfs->path_array[path_id].room[room_id];
		ft_printf("room_id: %d ", room_id);
		ft_printf("[%d] ", bfs->path_array[path_id].room[room_id]);
		ft_printf("[%d]\n", path_combo[combo_id].room[room_id]);
	}
	ft_printf("\n");
}

void	copy_path_combo(t_path_combo *best, t_path_combo *path)
{
	int	path_id;
	int	room_id;

	path_id = -1;
	while (path[++path_id].ants != -1)
	{
		ft_printf("! copied ants : %d ", path[path_id].ants);
		ft_printf(" size : %d !\n", path[path_id].size);
		best[path_id].ants = path[path_id].ants;
		best[path_id].size = path[path_id].size;
		if (!(best[path_id].room = ft_memalloc(sizeof(int) * best[path_id].size)))
			exit_error("Malloc Failed", (char*)__func__);
		room_id = -1;
		while (++room_id < path[path_id].size)
			best[path_id].room[room_id] = path[path_id].room[room_id];
	}
}

void	print_combo(t_p *p, t_path_combo *path)
{
	int	path_id;
	int	room_id;

	path_id = -1;
	ft_printf("++++ Combo Content ++++\n");
	while (path[++path_id].size != -1)
	{
		ft_printf("Ants: %d ", path[path_id].ants);
		ft_printf("Path Size: %d >>> ", path[path_id].size);
		room_id = -1;
		while (++room_id < path[path_id].size)
		{
			if (room_id != 0)
				ft_printf(" - ");
			ft_printf("[%s]", p->junction[path[path_id].room[room_id]].room_name);
		}
		ft_printf("\n");
	}
	ft_printf("\n");
	
}

int		get_room_connections(t_p *p, int room_id)
{
	int	x;
	int	y;
	int cpt;

	x = -1;
	cpt = 0;
	while (++x < p->data.room_count)
		if (p->matrix[x][room_id] != 0)
			cpt++;
	return (cpt);
}

int		get_test_limit(t_p *p)
{
	int	start;
	int	end;

	start = get_room_connections(p, p->data.rooms.start_index);
	end = get_room_connections(p, p->data.rooms.end_index);
	if (p->data.ant_count <= start && p->data.ant_count <= end)
		return (p->data.ant_count);
	if (start <= p->data.ant_count && start <= end)
		return (start);
	if (end <= p->data.ant_count && end <= start)
		return (end);
	return (-1);
}
