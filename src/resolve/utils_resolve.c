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

#include "../../includes/lem_in.h"

void		copy_path(t_bfs *bfs, t_path_combo *path_combo, int p_id, int c_id)
{
	int	r_id;

	path_combo[c_id].size = bfs->path_array[p_id].size;
	path_combo[c_id].ants = 0;
	if (!(path_combo[c_id].room = ft_memalloc(sizeof(t_room_status) *\
		bfs->path_array[p_id].size)))
		exit_error("Malloc Failed", (char*)__func__);
	r_id = -1;
	while (++r_id < bfs->path_array[p_id].size)
	{
		path_combo[c_id].room[r_id].id = bfs->path_array[p_id].room[r_id];
		path_combo[c_id].room[r_id].ant = -1;
	}
}

void		copy_path_combo(t_path_combo *best, t_path_combo *path, int limit)
{
	int	path_id;
	int	room_id;

	path_id = -1;
	while (++path_id < limit)
	{
		best[path_id].ants = path[path_id].ants;
		best[path_id].size = path[path_id].size;
		if (!(best[path_id].room = ft_memalloc(sizeof(t_room_status) *\
			best[path_id].size)))
			exit_error("Malloc Failed", (char*)__func__);
		room_id = -1;
		while (++room_id < path[path_id].size)
		{
			best[path_id].room[room_id].id = path[path_id].room[room_id].id;
			best[path_id].room[room_id].ant = -1;
		}
	}
}

static int	get_room_connections(t_p *p, int room_id)
{
	int	x;
	int cpt;

	x = -1;
	cpt = 0;
	while (++x < p->data.room_count)
		if (p->matrix[x][room_id] != 0)
			cpt++;
	return (cpt);
}

int			get_test_limit(t_p *p)
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
	exit_error("Test Limit Exited", (char*)__func__);
	return (-1);
}

/*
** void	print_combo(t_p *p, t_combo_data *cd)
** {
** 	int	path_id;
** 	int	room_id;
**
** 	path_id = -1;
** 	ft_printf("++++ Combo Content ++++\n");
** 	while (++path_id < cd->nb_path && cd->path_combo[path_id].size != -1)
** 	{
** 		ft_printf("Ants: %d ", cd->path_combo[path_id].ants);
** 		ft_printf("Path Size: %d >>> ", cd->path_combo[path_id].size);
** 		room_id = -1;
** 		while (++room_id < cd->path_combo[path_id].size)
** 		{
** 			if (room_id != 0)
** 				ft_printf(" - ");
** 			ft_printf("[%s]", p->junction[cd->path_combo[path_id]
** 										.room[room_id].id].room_name);
** 		}
** 		ft_printf("\n");
** 	}
** 	ft_printf("\n");
** }
*/
