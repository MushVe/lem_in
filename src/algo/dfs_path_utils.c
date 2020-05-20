/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs_path_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 16:05:21 by cseguier          #+#    #+#             */
/*   Updated: 2020/05/20 16:05:21 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

void		remove_bad_link(t_bfs *bfs, t_p *p)
{
	int i;

	i = 0;
	while (i < p->size)
	{
		if (bfs->rooms[i].score > bfs->final_score)
			bfs->rooms[i].token = -1;
		i++;
	}
}

void	ignore_path(t_path_array *path_array, int i_other_path)
{
	path_array[i_other_path].size = -1;
}

int		is_the_same(t_path_array *path_array, int i_current_path, int i_other_path)
{
	int	i_room;

	i_room = -1;
	while (++i_room < path_array[i_current_path].size)
		if (path_array[i_current_path].room[i_room] != path_array[i_other_path].room[i_room])
			return (0);
	return (1);
}

void save_path(t_p *p, t_bfs *bfs, int index, int size)
{
	if (index == p->data.rooms.start_index)
	{
		bfs->path_nb++;
		bfs_new_node(bfs->tmp_path, &bfs->path_list, size);
		return ;
	}
	else
	{
		bfs->tmp_path[size] = bfs->rooms[index].current_link;
		save_path(p, bfs, bfs->rooms[index].current_link, size + 1);
	}
}

void	reorder_path(t_bfs *bfs)
{
	quicksort(bfs);
	bfs->real_path_nb = find_n_kill_dopples(bfs->path_nb, bfs->path_array);
	bfs->path_array = clean_path_array(bfs->path_array, bfs->path_nb, bfs->real_path_nb);
	bfs->path_nb = bfs->real_path_nb;
}
