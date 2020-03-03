/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 01:27:16 by cseguier          #+#    #+#             */
/*   Updated: 2020/03/03 02:05:35 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	bfs_init(t_bfs *bfs, int size)
{
	int	i;

	if (!(bfs->visited_record = ft_memalloc(sizeof(int*) * size + 1))
		|| !(bfs->parent = ft_memalloc(sizeof(int*) * size + 1))
		|| !(bfs->path = ft_memalloc(sizeof(int*) * size + 1)))
		exit_error("Malloc Failed", (char*)__func__);
	i = 0;
	while (++i < size + 1)
		bfs->path[i] = -1;
}

void	find_path(t_bfs *bfs, int start, int end, int i, t_map_room_index *jun)
{
	bfs->path[i] = end;
	
	if (bfs->parent[end] != bfs->parent[start])
	{
		find_path(bfs, start, bfs->parent[end], ++i, jun);
		ft_printf("%s %d\n",
			jun[end].room_name, bfs->parent[end]);
	}
	else
	{
		ft_printf("%s %d\n",
			jun[end].room_name, bfs->parent[end]);
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

	while (q->rear != NULL && host != p->data.rooms.end_index)
	{
		host = q->front->data;
		de_queue(q);
		ft_printf("decu  ---> \t%s\t%d\n",
			p->junction[host].room_name, p->junction[host].index);
		link = -1;
		while (++link < p->size)
		{
			if (p->matrix[host][link] == 1
				&& bfs->visited_record[link] == 0)
			{
				en_queue(q, link);
				ft_printf("encu <--- \t%s\t%d\n",
					p->junction[link].room_name, p->junction[link].index);
				bfs->visited_record[link] = 1;
				bfs->parent[link] = host;
				ft_printf("parent/host %s <> link %s\n",
					 p->junction[host].room_name, p->junction[link].room_name);
			}
		}
	}

	if (host == p->data.rooms.end_index)
		find_path(bfs, p->data.rooms.start_index, p->data.rooms.end_index, 0, p->junction);

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