/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 01:27:16 by cseguier          #+#    #+#             */
/*   Updated: 2020/03/06 05:27:04 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	print_paths(t_p *p, t_bfs *bfs)
{
	t_path	*cpy;
	int		i;

	cpy = bfs->path;
	bfs->path_id = 0;
	while (cpy && ++bfs->path_id)
	{
		i = -1;
		while (++i < cpy->size)
		{
			ft_printf("Chemin #%d: ", bfs->path_id);
			ft_printf(" %s ", p->junction[cpy->data[i]].room_name);
			ft_printf(" %d ", cpy->data[i]);
			ft_printf(" %d\n", cpy->size);
		}
		ft_printf("++++++++++++++++++\n");
		cpy = cpy->next;
	}
}

void	reset_visited(t_p *p, t_bfs *bfs)
{
	int	i;

	i = -1;
	while (++i < p->size)
		bfs->visited_record[i] = 0;
}

void	get_matrix_level(t_p *p, t_bfs *bfs)
{
	int	i;
	int	j;

	i = -1;
	while (++i < p->size)
	{
		j = -1;
		while (++j < p->size)
			if (p->matrix[i][j] > 0)
				bfs->matrix_level[i] = p->matrix[i][j];
	}
}

void	print_matrix(t_p *p, t_bfs *bfs, int i, int j)
{
	ft_printf("   ");
	i = p->size;
	while (--i >= 0)
		ft_printf("%s ", p->junction[i].room_name);
	ft_printf("\n");
	i = p->size;
	while (--i >= 0)
	{
		ft_printf("%s  ", p->junction[i].room_name);
		j = p->size;
		while (--j >= 0)
		{
			if (i == j)
				ft_printf("  ");
			else if (p->matrix[i][j] == 0)
				ft_printf(". ");
			else if (p->matrix[i][j] == __INT_MAX__)
				ft_printf("X ");
			else
				ft_printf("%d ", p->matrix[i][j]);
		}
		ft_printf("    %d\n", bfs->matrix_level[i]);
	}
}

void	bfs_init(t_bfs *bfs, int size)
{
	int	i;

	if (!(bfs->visited_record = ft_memalloc(sizeof(int) * size))
		|| !(bfs->parent = ft_memalloc(sizeof(int) * size))
		|| !(bfs->tmp_path = ft_memalloc(sizeof(int) * size))
		|| !(bfs->matrix_level = ft_memalloc(sizeof(int) * size)))
		exit_error("Malloc Failed", (char*)__func__);
	i = -1;
	while (++i < size)
		bfs->tmp_path[i] = -1;
	bfs->max_path = 0;
	bfs->path = NULL;
}

int	find_path(t_bfs *bfs, t_p *p, int host, int i)
{
	int	link;

	link = -1;
	bfs->tmp_path[i] = p->junction[host].index;
	bfs->visited_record[host] = 1;
	if (host != p->data.rooms.start_index)
	{
		while (++link < p->size)
		{
			if (p->matrix[link][host] > 0
				&& bfs->visited_record[link] == 0
				&& bfs->matrix_level[link] <= bfs->matrix_level[host])
				if (find_path(bfs, p, link, i + 1))
					return (1);
		}
	}
	else
		bfs_new_node(bfs->tmp_path, &bfs->path, i + 1);
	bfs->tmp_path[i] = -1;
	bfs->visited_record[host] = 0;
	return (0);
}

int	algo(t_p *p, t_bfs *bfs)
{
	t_queue	*q;
	int		host;
	int		link;

	bfs_init(bfs, p->size);
	q = create_queue();
	host = p->data.rooms.start_index;
	en_queue(q, p->junction[host].index);
	bfs->visited_record[host] = 1;
	while (q->rear != NULL)
	{
		host = q->front->data;
		de_queue(q);
		link = -1;
		while (++link < p->size)
		{
			if (p->matrix[host][link] != 0)
			{
				if (host == p->data.rooms.end_index)
				{
					p->matrix[host][link] = __INT_MAX__;
					bfs->max_path++;
				}
				else
				{
					p->matrix[host][link] = p->matrix[bfs->parent[host]][host] + 1;
					if (bfs->visited_record[link] == 0)
					{
						en_queue(q, link);
						bfs->visited_record[link] = 1;
						bfs->parent[link] = host;
					}
				}
			}
		}
	}
	get_matrix_level(p, bfs);
	print_matrix(p, bfs, 0, 0);
	reset_visited(p, bfs);
	find_path(bfs, p, p->data.rooms.end_index, 0);
	print_paths(p, bfs);
	return (0);
}
