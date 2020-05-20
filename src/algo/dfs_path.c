/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 16:05:06 by cseguier          #+#    #+#             */
/*   Updated: 2020/05/20 19:34:23 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

int				find_n_kill_dopples(int path_nb, t_path_array *paths)
{
	int	next;
	int	cur;
	int	real_nb;

	real_nb = path_nb;
	cur = -1;
	while (++cur < path_nb)
	{
		next = cur;
		while (++next < path_nb)
		{
			if (paths[next].size == -1 || paths[next].size > paths[cur].size)
				break ;
			if (paths[next].size != -1 && paths[next].size == paths[cur].size)
			{
				if (is_the_same(paths, cur, next))
				{
					real_nb--;
					ignore_path(paths, next);
				}
			}
		}
	}
	return (real_nb);
}

t_path_array	*clean_path_array(t_path_array *paths, int path_nb, int real_nb)
{
	t_path_array	*real_array;
	int				i;
	int				r;

	if (!(real_array = ft_memalloc((sizeof(t_path_array) * real_nb))))
		exit_error("Malloc Failed", (char*)__func__);
	i = -1;
	r = -1;
	while (++i < path_nb && r < real_nb)
	{
		if (paths[i].size != -1)
		{
			real_array[++r].room = paths[i].room;
			real_array[r].size = paths[i].size;
		}
		else
			ft_memdel((void*)&paths[i].room);
	}
	ft_memdel((void*)&paths);
	return (real_array);
}

static int		get_to_end(t_p *p, t_room_infos *rooms, int curr)
{
	int best_room_index;

	if (curr == p->data.rooms.end_index)
		return (1);
	if ((best_room_index = find_best_room(rooms, curr, 0)) != -1)
	{
		rooms[best_room_index].current_link = curr;
		return (get_to_end(p, rooms, best_room_index));
	}
	return (0);
}

static int		get_to_start(t_p *p, t_room_infos *rooms, int curr, t_bfs *bfs)
{
	int best_room_index;

	if (curr == p->data.rooms.start_index)
	{
		bfs->tmp_path[0] = p->data.rooms.end_index;
		save_path(p, bfs, p->data.rooms.end_index, 1);
		return (1);
	}
	if ((best_room_index = find_best_room(rooms, curr, 1)) != -1)
	{
		rooms[curr].current_link = best_room_index;
		return (get_to_start(p, rooms, best_room_index, bfs));
	}
	return (0);
}

int				create_path(t_p *p, t_bfs *bfs)
{
	t_room_infos	*rooms;
	int				next;

	rooms = bfs->rooms;
	next = 0;
	while (next < p->size)
	{
		if (rooms[next].token != -1 && next != p->data.rooms.start_index)
		{
			if (get_to_end(p, rooms, next) == 1)
				get_to_start(p, rooms, next, bfs);
		}
		next++;
	}
	return (1);
}
