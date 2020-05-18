/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 01:27:16 by cseguier          #+#    #+#             */
/*   Updated: 2020/04/24 18:21:56 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

// static int	find_path(t_bfs *bfs, t_p *p, int host, int i)
// {
// 	int	link;

// 	link = -1;
// 	bfs->tmp_path[i] = p->junction[host].index;
// 	bfs->visited_record[host] = 1;
// 	if (host != p->data.rooms.start_index)
// 	{
// 		while (++link < p->size)
// 		{
// 			if (p->matrix[link][host] > 0 && bfs->visited_record[link] == 0
// 				&& bfs->matrix_level[link] <= bfs->matrix_level[host])
// 				if (find_path(bfs, p, link, i + 1))
// 					return (1);
// 		}
// 	}
// 	else
// 	{
// 		bfs_new_node(bfs->tmp_path, &bfs->path_list, i + 1);
// 		bfs->path_nb++;
// 		if (bfs->path_nb == 5000)
// 			return (1);
// 	}
// 	bfs->tmp_path[i] = -1;
// 	bfs->visited_record[host] = 0;
// 	return (0);
// }

// static void	treat_unvisited(t_p *p, t_bfs *bfs, t_queue **q)
// {
// 	if (bfs->host == p->data.rooms.end_index)
// 	{
// 		p->matrix[bfs->host][bfs->link] = __INT_MAX__;
// 		bfs->max_path++;
// 	}
// 	else
// 	{
// 		p->matrix[bfs->host][bfs->link] = 
// 			p->matrix[bfs->parent[bfs->host]][bfs->host] + 1;
// 		if (bfs->visited_record[bfs->link] == 0)
// 		{
// 			en_queue(*q, bfs->link);
// 			bfs->visited_record[bfs->link] = 1;
// 			bfs->parent[bfs->link] = bfs->host;
// 		}
// 	}
// }

// static void	do_bfs(t_p *p, t_bfs *bfs)
// {
// 	t_queue	*q;

// 	q = create_queue();
// 	bfs->host = p->data.rooms.start_index;
// 	en_queue(q, p->junction[bfs->host].index);
// 	bfs->visited_record[bfs->host] = 1;
// 	while (q->rear != NULL)
// 	{
// 		bfs->host = q->front->data;
// 		de_queue(q);
// 		bfs->link = -1;
// 		while (++bfs->link < p->size)
// 			if (p->matrix[bfs->host][bfs->link] != 0)
// 				treat_unvisited(p, bfs, &q);
// 	}
// 	ft_memdel((void*)&q);
// }

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
	ft_printf("%d\n", bfs->final_score);
}

static void do_dfs_from_start(t_p *p, t_bfs *bfs, int current_room, int distance)
{
	t_room_infos *rooms;
	int			cpt;
	int			link_id;

	if (distance != 0 && current_room == p->data.rooms.start_index)
		return ;
	rooms = bfs->rooms;
	rooms[current_room].distance_start = distance;
	// ft_printf("[%s] ", p->junction[current_room].room_name);
	// ft_printf("distance:%ld ", distance);
	// ft_printf("d_start:%ld\n", rooms[current_room].distance_start);
	if (current_room == p->data.rooms.end_index)
		return ;
	cpt = -1;
	while (++cpt < rooms[current_room].nb_link)
	{
		link_id = rooms[current_room].link_array[cpt];
		// ft_printf("   %d\t", link);
		// ft_printf("[%s] %d\n", p->junction[rooms[current_room].link_array[link]].room_name, rooms[current_room].link_array[link]);
		if (rooms[link_id].token != -1 && (rooms[link_id].distance_start == 0 || rooms[link_id].distance_start > distance))
				do_dfs_from_start(p, bfs, link_id, distance + 1);
	}
	if (rooms[current_room].nb_link < 2 && current_room != p->data.rooms.start_index)
		rooms[current_room].token = -1;
}

static void do_dfs_from_end(t_p *p, t_bfs *bfs, int current_room, int distance)
{
	t_room_infos *rooms;
	int			cpt;
	int			link_id;

	// ft_printf("%d %d %d            ", distance, current_room, p->data.rooms.end_index);
	// possible problemes avec la facon dont la map est stockée
	if (distance != 0 && current_room == p->data.rooms.end_index)
	{
		// ft_printf("%s is end\n", __func__);
		return ;
	}
	
	rooms = bfs->rooms;
	rooms[current_room].distance_end = distance;
	rooms[current_room].score = rooms[current_room].distance_end + rooms[current_room].distance_start;
	cpt = -1;
	
	// ft_printf("[%s] ", p->junction[current_room].room_name);
	// ft_printf("distance:%ld ", distance);
	// ft_printf("d_start:%ld ", rooms[current_room].distance_start);
	// ft_printf("d_end:%ld ", rooms[current_room].distance_end);
	// // ft_printf("score:%ld\n", rooms[current_room].score);
	
	if (current_room == p->data.rooms.start_index)
	{
		// ft_printf("%s is start\n", __func__);
		return ;
	}

	while (++cpt < rooms[current_room].nb_link)
	{
		link_id = rooms[current_room].link_array[cpt];
		if (rooms[link_id].token != -1 && (rooms[link_id].distance_end == 0 || rooms[link_id].distance_end > distance))
			do_dfs_from_end(p, bfs, link_id, distance + 1);
	}

	if (rooms[current_room].nb_link < 2 && current_room != p->data.rooms.end_index)
	{
		// ft_printf("%s dead\n", __func__);
		rooms[current_room].token = -1;
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

int find_best_room(t_p *p, t_room_infos *rooms, int host, int way)
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
		// ft_printf("%d\n", link_id);
		if (rooms[link_id].score <= rooms[host].score && is_closer(&d_start, &d_end, way, rooms[link_id]))
			return (link_id);
		i++;
	}
	return (-1);
}

// int find_best_room(t_p *p, t_room_infos *rooms, int host, int way)
// {
// 	int d_start;
// 	int d_end;
// 	int i;

// 	d_start = rooms[host].distance_start;
// 	d_end = rooms[host].distance_end;
// 	i = 0;
// 	while (i < p->size)
// 	{
// 		if (p->matrix[host][i] != 0)
// 		{
// 			ft_printf("%d\n", i);
// 			if (rooms[i].score <= rooms[host].score && is_closer(&d_start, &d_end, way, rooms[i]))
// 				return (i);
// 		}
// 		i++;
// 	}
// 	return (-1);
// }

int get_to_end(t_p *p, t_room_infos *rooms, int curr)
{
	int best_room_index;

	// ft_printf("Room tested in %s: [%s] [%d]\n", __func__, p->junction[curr].room_name, curr);
	if (curr == p->data.rooms.end_index)
		return (1);
	if ((best_room_index = find_best_room(p, rooms, curr, 0)) != -1)
	{
		// ft_printf("(%d)[%s] contain (%d)[%s]\n", best_room_index, p->junction[best_room_index].room_name, curr, p->junction[curr].room_name);
		rooms[best_room_index].current_link = curr;
		return (get_to_end(p, rooms, best_room_index));
	}
	return (0);
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

int get_to_start(t_p *p, t_room_infos *rooms, int curr, t_bfs *bfs)
{
	int best_room_index;

	// ft_printf("Room tested in %s: [%s] [%d]\n", __func__, p->junction[curr].room_name, curr);
	if (curr == p->data.rooms.start_index)
	{
		bfs->tmp_path[0] = p->data.rooms.end_index;
		save_path(p, bfs, p->data.rooms.end_index, 1);
		return (1);
	}
	if ((best_room_index = find_best_room(p, rooms, curr, 1)) != -1)
	{
		// ft_printf("(%d)[%s] contain (%d)[%s]\n", best_room_index, p->junction[best_room_index].room_name, curr, p->junction[curr].room_name);
		rooms[curr].current_link = best_room_index;
		return (get_to_start(p, rooms, best_room_index, bfs));
	}
	return (0);
}

int			dfs_solve(t_p *p, t_bfs *bfs)
{
	t_room_infos	*rooms;
	int				next;
	
	rooms = bfs->rooms;
	next = 0;
	ft_printf("\n ------ in [%s] ------\n", __func__);
	while (next < p->size)
	{
		// ft_printf("------> Room tested in %s: [%s]\n", __func__, p->junction[next].room_name);
		if (rooms[next].token != -1 && next != p->data.rooms.start_index)
		{
			if (get_to_end(p, rooms, next) == 1)
				get_to_start(p, rooms, next, bfs);
		}
		next++;
	}
	return 1;
}

static void		remove_bad_link(t_bfs *bfs, t_p *p)
{
	int i;

	i = 0;
	while (i < p->size)
	{
		if (bfs->rooms[i].score > bfs->final_score)
		{
			// ft_printf("[%s]\n", p->junction[i].room_name);
			bfs->rooms[i].token = -1;
		}
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

int	find_n_kill_dopples(t_p *p, int	path_nb, t_path_array *path_array)
{
	int	i_other_path;
	int	i_current_path;
	int	real_path_nb;
	int	id_alias;
	int	room_id;

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
					// ft_printf("current:");
					// room_id = -1;
					// while (++room_id < path_array[i_current_path].size)
					// {id_alias = path_array[i_current_path].room[room_id];
					// ft_printf(" - [%s]", p->junction[id_alias].room_name);}
					// ft_printf("\nother:  ");
					// room_id = -1;
					// while (++room_id < path_array[i_other_path].size)
					// {id_alias = path_array[i_other_path].room[room_id];
					// ft_printf(" - [%s]", p->junction[id_alias].room_name);}
					// ft_printf("\n\n");

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
	// ft_printf("path nb = %d\n", path_nb);
	while (++i < path_nb && r < real_path_nb)
	{
		// ft_printf("rp:%d r:%d\n", real_path_nb, r);	
		if (path_array[i].size != -1)
		{
			// r++;
			real_array[++r].room = path_array[i].room;
			// path_array[i].size++;
			real_array[r].size = path_array[i].size;
		}
		// }
		// else
		// 	ft_memdel((void*)&path_array[i].room);
	}
	// ft_memdel((void*)&path_array);
	return (real_array);
}

void	reorder_path(t_p *p, t_bfs *bfs)
{
	quicksort(bfs);
	// print_path_array(p, bfs);
	bfs->real_path_nb = find_n_kill_dopples(p, bfs->path_nb, bfs->path_array);
	bfs->path_array = clean_path_array(bfs->path_array, bfs->path_nb, bfs->real_path_nb);
	bfs->path_nb = bfs->real_path_nb;
	// print_path_array(p, bfs);
}

int			algo(t_p *p, t_bfs *bfs)
{
	bfs_init(bfs, p->size);
	set_nb_link(p, bfs);
	ft_printf("b4 set from start\n");
	do_dfs_from_start(p, bfs, p->data.rooms.start_index, 0);
	ft_printf("AFTER set from start\n");
	ft_printf("\n");
	ft_printf("b4 set from end\n");
	do_dfs_from_end(p, bfs, p->data.rooms.end_index, 0);
	ft_printf("AFTER set from end\n");
	get_ultimate_result(p, bfs);
	remove_bad_link(bfs, p);
	get_test_limit(p);

	dfs_solve(p, bfs);

	fill_path_array(bfs);
	// sort + supress doubles
	reorder_path(p, bfs);
	
	// do_bfs(p, bfs);
	// get_matrix_level(p, bfs);
	// reset_visited(p, bfs);
	// find_path(bfs, p, p->data.rooms.end_index, 0);
	// fill_path_array(bfs);
	// bfs_free_all(bfs, p->size);
	// bfs_free_list(&bfs->path_list);
	// ft_printf("end of algo\n");
	return (0);
}

/*
**	print_matrix(p, bfs, 0, 0);
**	print_path_array(p, bfs);
*/
