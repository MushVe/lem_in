/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 16:05:06 by cseguier          #+#    #+#             */
/*   Updated: 2020/05/20 16:05:06 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

int	find_n_kill_dopples(int	path_nb, t_path_array *path_array)
{
	int	i_other_path;
	int	i_current_path;
	int	real_path_nb;


	real_path_nb = path_nb;
	i_current_path = -1;
	while (++i_current_path < path_nb)
	{
		i_other_path = i_current_path;
		while (++i_other_path < path_nb)
		{
			if (path_array[i_other_path].size == -1 || path_array[i_other_path].size > path_array[i_current_path].size)
				break ;
			if (path_array[i_other_path].size != -1 && path_array[i_other_path].size == path_array[i_current_path].size)
			{
				if (is_the_same(path_array, i_current_path, i_other_path))
				{
					real_path_nb--;
					ignore_path(path_array, i_other_path);
				}
			}
		}
	}
	return (real_path_nb);
}

t_path_array	*clean_path_array(t_path_array *path_array, int path_nb, int real_path_nb)
{
	t_path_array *real_array;
	int	i;
	int	r;

	if (!(real_array = ft_memalloc((sizeof(t_path_array) * real_path_nb))))
		exit_error("Malloc Failed", (char*)__func__);
	i = -1;
	r = -1;
	while (++i < path_nb && r < real_path_nb)
	{
		if (path_array[i].size != -1)
		{
			real_array[++r].room = path_array[i].room;
			real_array[r].size = path_array[i].size;
		}
		else
			ft_memdel((void*)&path_array[i].room);
	}
	ft_memdel((void*)&path_array);
	return (real_array);
}

static int get_to_end(t_p *p, t_room_infos *rooms, int curr)
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

static int get_to_start(t_p *p, t_room_infos *rooms, int curr, t_bfs *bfs)
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

int			create_path(t_p *p, t_bfs *bfs)
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
	return 1;
}