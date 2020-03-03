/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 01:27:16 by cseguier          #+#    #+#             */
/*   Updated: 2020/03/03 05:41:18 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	bfs_init(t_bfs *bfs, int size)
{
	int	i;

	if (!(bfs->visited_record = ft_memalloc(sizeof(int*) * size))
		|| !(bfs->parent = ft_memalloc(sizeof(int*) * size))
		|| !(bfs->tmp_path = ft_memalloc(sizeof(int*) * size)))
		exit_error("Malloc Failed", (char*)__func__);
	i = 0;
	bfs->max_path = 0;
}

int		*find_path(t_bfs *bfs, t_p *p, int end, int i)
{
	// ft_printf("AAAA\n");
	bfs->path[bfs->path_id][i] = p->data.rooms.end_index;
	// ft_printf("BBBB\n");
	if (end != p->data.rooms.start_index)
	{
		// ft_printf("CCCC\n");
		find_path(bfs, p, bfs->parent[end], ++i);
		ft_printf("%s\n", p->junction[end].room_name);
	}
	else
	{
		ft_printf("%s\n", p->junction[end].room_name);
		return ;
	}
}

int algo(t_p *p, t_bfs *bfs)
{
	t_queue	*q;
	int		host;
	int		link;

	bfs_init(bfs, p->size);
	q = create_queue();
	host = p->data.rooms.start_index;

	ft_printf("start:  %s\t%d\n", p->data.rooms.start, p->data.rooms.start_index);
	ft_printf("end:    %s\t%d\n", p->data.rooms.end, p->data.rooms.end_index);

	en_queue(q, p->junction[host].index);
	bfs->visited_record[host] = 1;

	while (q->rear != NULL)
	{
		host = q->front->data;
		de_queue(q);
		// ft_printf("decu  ---> \t%s\t%d\n", p->junction[host].room_name, p->junction[host].index);
		link = -1;
		while (++link < p->size)
		{
			if (p->matrix[host][link] == 1
				&& bfs->visited_record[link] == 0)
			{
				en_queue(q, link);
				// ft_printf("encu <---  \t%s\t%d\n", p->junction[link].room_name, p->junction[link].index);
				bfs->visited_record[link] = 1;
				bfs->parent[link] = host;
				if (host == p->data.rooms.end_index || link == p->data.rooms.end_index)
					bfs->max_path++;
				ft_printf("            %s <> %s\n", p->junction[host].room_name, p->junction[link].room_name);
			}
		}
	}

	ft_printf("max_path: %d\n", bfs->max_path);
	// ft_printf("000\n");

	bfs->path_id = -1;
	
	while (++bfs->path_id < bfs->max_path)
	{
		bfs->tmp_path = find_path(bfs, p, p->data.rooms.end_index, 0);
		bfs_new_node(bfs->tmp_path, p->size, p);
		
	}

	// int i = p->size;
	// //bfs->path = rev(bfs->path, p->size);
	// while (--i > -1)
	// {
	// 	ft_printf("%s\n", p->junction[bfs->path[i]].room_name);
	// }
	return (0);
}


/*
int i = -1;
int j = -1;
while (i++)
	while (j++)
		matrix[host][1 + i + j];

  0 1 2 3 4 5
0 * . 1 1 . .
1 . * . . 1 1
2 1 . * 1 . 1
3 1 . 1 * . .
4 . 1 . . * 1
5 . 1 1 . 1 *

*/