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
		if (path[i].ants + path[i].size < path[cible_max].ants +\
			path[cible_max].size)
			cible_max = i;
		if (path[i].ants + path[i].size > path[cible_min].ants +\
			path[cible_min].size)
			cible_min = i;
	}
	if (marge < 0)
		return (cible_max);
	return (cible_min);
}
