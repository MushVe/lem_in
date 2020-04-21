/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 01:27:16 by cseguier          #+#    #+#             */
/*   Updated: 2020/03/07 06:22:54 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static void	reset_visited(t_p *p, t_bfs *bfs)
{
	int	i;

	i = -1;
	while (++i < p->size)
		bfs->visited_record[i] = 0;
}

static int	find_path(t_bfs *bfs, t_p *p, int host, int i)
{
	int	link;

	link = -1;
	bfs->tmp_path[i] = p->junction[host].index;
	bfs->visited_record[host] = 1;
	//ft_printf("+++ findpath start\n");
	if (host != p->data.rooms.start_index)
	{
		//ft_printf("+++ findpath 000\n");
		while (++link < p->size)
		{
			//ft_printf("+++ findpath 111\n");
			if (p->matrix[link][host] > 0
				&& bfs->visited_record[link] == 0
				&& bfs->matrix_level[link] <= bfs->matrix_level[host])
				if (find_path(bfs, p, link, i + 1))
					return (1);
		}
		//ft_printf("+++ findpath 222\n");
	}
	else
	{
		//ft_printf("+++ findpath 333\n");
		bfs_new_node(bfs->tmp_path, &bfs->path_list, i + 1);
		//ft_printf("+++ findpath 444\n");
		bfs->path_nb++;
	}
	//ft_printf("+++ findpath 555\n");
	bfs->tmp_path[i] = -1;
	//ft_printf("+++ findpath 666\n");
	bfs->visited_record[host] = 0;
	//ft_printf("+++ findpath end\n");
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
		p->matrix[bfs->host][bfs->link] = \
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
		{
			if (p->matrix[bfs->host][bfs->link] != 0)
			{
				treat_unvisited(p, bfs, &q);
			}
		}
	}
}

int			algo(t_p *p, t_bfs *bfs)
{
	ft_printf("++ algo init\n");
	bfs_init(bfs, p->size);
	ft_printf("++ algo dobfs\n");
	do_bfs(p, bfs);
	ft_printf("++ algo getmatrixlvl\n");
	get_matrix_level(p, bfs);
	ft_printf("++ algo resetvisited\n");
	reset_visited(p, bfs);
	ft_printf("++ algo findpath\n");
	find_path(bfs, p, p->data.rooms.end_index, 0);
	ft_printf("++ algo fillpatharray\n");
	fill_path_array(p, bfs);
	ft_printf("++ algo free\n");
//	print_path_array(p, bfs);
	bfs_free_list(&bfs->path_list);
	ft_printf("++ algo init\n");
	return (0);
}
