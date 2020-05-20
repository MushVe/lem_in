/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 01:27:16 by cseguier          #+#    #+#             */
/*   Updated: 2020/05/20 18:38:03 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

static int	find_path(t_bfs *bfs, t_p *p, int host, int i)
{
	int	link;

	link = -1;
	bfs->tmp_path[i] = p->junction[host].index;
	bfs->visited_record[host] = 1;
	if (host != p->data.rooms.start_index)
	{
		while (++link < p->size)
		{
			if (p->matrix[link][host] > 0 && bfs->visited_record[link] == 0
				&& bfs->matrix_level[link] <= bfs->matrix_level[host])
				if (find_path(bfs, p, link, i + 1))
					return (1);
		}
	}
	else
	{
		bfs_new_node(bfs->tmp_path, &bfs->path_list, i + 1);
		bfs->path_nb++;
		if (bfs->path_nb == 5000)
			return (1);
	}
	bfs->tmp_path[i] = -1;
	bfs->visited_record[host] = 0;
	return (0);
}

static void	treat_unvisited(t_p *p, t_bfs *bfs, t_queue **q)
{
	if (bfs->host == p->data.rooms.end_index)
	{
		p->matrix[bfs->host][bfs->link] = __INT_MAX__;
		bfs->max_path++;
	}
	else
	{
		p->matrix[bfs->host][bfs->link] = 
			p->matrix[bfs->parent[bfs->host]][bfs->host] + 1;
		if (bfs->visited_record[bfs->link] == 0)
		{
			en_queue(*q, bfs->link);
			bfs->visited_record[bfs->link] = 1;
			bfs->parent[bfs->link] = bfs->host;
		}
	}
}

static void	do_bfs(t_p *p, t_bfs *bfs)
{
	t_queue	*q;

	q = create_queue();
	bfs->host = p->data.rooms.start_index;
	en_queue(q, p->junction[bfs->host].index);
	bfs->visited_record[bfs->host] = 1;
	while (q->rear != NULL)
	{
		bfs->host = q->front->data;
		de_queue(q);
		bfs->link = -1;
		while (++bfs->link < p->size)
			if (p->matrix[bfs->host][bfs->link] != 0)
				treat_unvisited(p, bfs, &q);
	}
	ft_memdel((void*)&q);
}

void		bfs_solve(t_p *p, t_bfs *bfs)
{
	do_bfs(p, bfs);
	get_matrix_level(p, bfs);
	reset_visited(p, bfs);
	find_path(bfs, p, p->data.rooms.end_index, 0);
	fill_path_array(bfs);
	quicksort(bfs);
}

int			algo(t_p *p, t_bfs *bfs)
{
	bfs_init(bfs, p->size);
	if (p->data.room_count > 400)
		dfs_solve(p, bfs);
	else
		bfs_solve(p, bfs);
	bfs_free_all(bfs);
	bfs_free_list(&bfs->path_list);
	return (0);
}

//FIXME: MAP AVEC AUCUN CHEMIN

/*
**	print_matrix(p, bfs, 0, 0);
**	print_path_array(p, bfs);
*/
