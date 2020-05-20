/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 16:05:42 by cseguier          #+#    #+#             */
/*   Updated: 2020/05/20 16:05:42 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

int	is_closer(int *d_start, int *d_end, int way, t_room_infos current)
{
	if (current.token == -1)
		return (0);
	if (way == 1)
	{
		if (*d_start <= current.distance_start)
			return (0);
		*d_start = current.distance_start;
		*d_end = current.distance_end;
	}
	else
	{
		if (*d_end <= current.distance_end)
			return (0);
		*d_start = current.distance_start;
		*d_end = current.distance_end;
	}
	return (1);
}

int find_best_room(t_room_infos *rooms, int host, int way)
{
	int d_start;
	int d_end;
	int i;
	int link_id;

	d_start = rooms[host].distance_start;
	d_end = rooms[host].distance_end;
	i = 0;
	while (i < rooms[host].nb_link)
	{
		link_id = rooms[host].link_array[i];
		if (rooms[link_id].score <= rooms[host].score && is_closer(&d_start, &d_end, way, rooms[link_id]))
			return (link_id);
		i++;
	}
	return (-1);
}

void		get_ultimate_result(t_p *p, t_bfs *bfs)
{
	int	i;
	t_room_infos *rooms;
	int link;

	i = -1;
	rooms = bfs->rooms;
	if (rooms[p->data.rooms.end_index].nb_link > rooms[p->data.rooms.start_index].nb_link)
		link = p->data.rooms.start_index;
	else
		link = p->data.rooms.end_index;
	while (++i < p->size)
	{
		if (p->matrix[link][i] != 0)
		{
			if (bfs->rooms[i].token != -1 && (bfs->final_score == 0 || bfs->final_score < bfs->rooms[i].score))
				bfs->final_score = bfs->rooms[i].score;
		}
	}
}

void		set_nb_link(t_p *p, t_bfs *bfs)
{
	int		i;
	int		j;
	int		z;
	int		links;

	i = -1;
	while (++i < p->size)
	{
		links = 0;
		j = -1;
		z = -1;
		if (!(bfs->rooms[i].link_array = ft_memalloc(sizeof(int) * p->size)))
			exit_error("Malloc Error\n", (char*)__func__);
		while (++j < p->size)
		{
			if (p->matrix[i][j] != 0)
			{
				bfs->rooms[i].link_array[++z] = j;
				links++;
			}
		}
		bfs->rooms[i].nb_link = links;
	}
}
