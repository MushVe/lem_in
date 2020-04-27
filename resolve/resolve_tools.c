/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 15:59:09 by cseguier          #+#    #+#             */
/*   Updated: 2020/03/12 19:02:05 by cseguier         ###   ########.fr       */
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

int		collide(t_bfs *bfs, t_path_combo *combo, int target_id)
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

void	free_path_combo(t_path_combo *combo, int nb_path)
{
	int	i;

	i = -1;
	while (++i < nb_path)
		ft_memdel((void*)&combo[i].room);
	ft_memdel((void*)&combo);
}

void	init_utils(t_p *p, t_combo_data *cd, t_combo_utils *u)
{
	u->test_id = -1;
	u->nb_total_ants = p->data.ant_count;
	u->best_nb_lines = __INT_MAX__;
	u->best_nb_path = 0;
	u->test_limit = get_test_limit(p);
	cd->nb_path = 0;
}
