/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 19:00:46 by cseguier          #+#    #+#             */
/*   Updated: 2020/05/20 19:07:09 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

static void	do_dfs_from_start(t_p *p, t_bfs *bfs, int current, int distance)
{
	t_room_infos	*rooms;
	int				cpt;
	int				link_id;

	if (distance != 0 && current == p->data.rooms.start_index)
		return ;
	rooms = bfs->rooms;
	rooms[current].distance_start = distance;
	if (current == p->data.rooms.end_index)
		return ;
	cpt = -1;
	while (++cpt < rooms[current].nb_link)
	{
		link_id = rooms[current].link_array[cpt];
		if (rooms[link_id].token != -1 && (rooms[link_id].distance_start == 0
			|| rooms[link_id].distance_start > distance))
			do_dfs_from_start(p, bfs, link_id, distance + 1);
	}
	if (rooms[current].nb_link < 2 && current != p->data.rooms.start_index)
		rooms[current].token = -1;
}

static void	do_dfs_from_end(t_p *p, t_bfs *bfs, int current_room, int distance)
{
	t_room_infos	*rooms;
	int				cpt;
	int				link_id;

	if (distance != 0 && current_room == p->data.rooms.end_index)
		return ;
	rooms = bfs->rooms;
	rooms[current_room].distance_end = distance;
	rooms[current_room].score = rooms[current_room].distance_end +
		rooms[current_room].distance_start;
	cpt = -1;
	if (current_room == p->data.rooms.start_index)
		return ;
	while (++cpt < rooms[current_room].nb_link)
	{
		link_id = rooms[current_room].link_array[cpt];
		if (rooms[link_id].token != -1 && (rooms[link_id].distance_end == 0 ||
			rooms[link_id].distance_end > distance))
			do_dfs_from_end(p, bfs, link_id, distance + 1);
	}
	if (rooms[current_room].nb_link < 2 && current_room !=
		p->data.rooms.end_index)
		rooms[current_room].token = -1;
}

void		dfs_solve(t_p *p, t_bfs *bfs)
{
	set_nb_link(p, bfs);
	do_dfs_from_start(p, bfs, p->data.rooms.start_index, 0);
	do_dfs_from_end(p, bfs, p->data.rooms.end_index, 0);
	get_ultimate_result(p, bfs);
	remove_bad_link(bfs, p);
	get_test_limit(p);
	create_path(p, bfs);
	fill_path_array(bfs);
	reorder_path(bfs);
}
