/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 01:27:16 by cseguier          #+#    #+#             */
/*   Updated: 2020/03/05 07:46:56 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

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
	int j;

	link = -1;
	// ft_printf("++ NEW ROUND %d %s ++\n", i, p->junction[host].room_name);
	bfs->tmp_path[i] = p->junction[host].index;
	if (host != p->data.rooms.start_index)
	{
		while (++link < p->size)
		{
			// ft_printf("host:  %s   link:  %s   ", p->junction[host].room_name, p->junction[link].room_name);
			// ft_printf("matrix:  %10d   level:  %10d\n", p->matrix[link][host], bfs->matrix_level[host]);
			if (p->matrix[link][host] > 0 && bfs->matrix_level[link] < bfs->matrix_level[host])
			{
				// ft_printf("findpath-> host: %s  link: %s\n", p->junction[host].room_name, p->junction[link].room_name);
				if(find_path(bfs, p, link, i + 1))
					return (1);
				//break;
			}
		}
	}
	else
	{
		j = -1;
		while (bfs->tmp_path[++j] != -1)
		{
			ft_printf("<<<>>>>   %s ", p->junction[bfs->tmp_path[j]].room_name);
			ft_printf(" %d\n", bfs->tmp_path[j]);
		}
		// 	bfs->tmp_path[i] = -1;
		// 	return (0);
	}
	ft_printf("++++++++++++++++++++++\n");
	bfs->tmp_path[i] = -1;
	return (0);
}

// void	find_all_paths(t_bfs *bfs, t_p *p, int host)
// {
// 	int	link;

// 	link = -1;
// 	while (++link < p->size)
// 	{
// 		if (p->matrix[host][link] > 0 && p->matrix[host][link] < bfs->matrix_level[host])
// 			find_path(bfs, p, link, ++i);
// 	}
// }

int algo(t_p *p, t_bfs *bfs)
{
	t_queue	*q;
	int		host;
	int		link;
	int		i;
	int		j;

	bfs_init(bfs, p->size);
	q = create_queue();
	host = p->data.rooms.start_index;

	// ft_printf("start:  %s\t%d\n", p->data.rooms.start, p->data.rooms.start_index);
	// ft_printf("end:    %s\t%d\n", p->data.rooms.end, p->data.rooms.end_index);

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
						// ft_printf("encu <---  \t%s\t%d\n", p->junction[link].room_name, p->junction[link].index);
						bfs->visited_record[link] = 1;
						bfs->parent[link] = host;
							
						// ft_printf("            %s <> %s\n", p->junction[host].room_name, p->junction[link].room_name);
					}
				}
			}
		}
	}

	i = -1;
	while (++i < p->size)
	{
		j = -1;
		while (++j < p->size)
			if (p->matrix[i][j] > 0)
				bfs->matrix_level[i] = p->matrix[i][j];
	}

	// ft_printf("   ");
	// i = p->size;
	// while (--i >= 0)
	// {
	// 	ft_printf("%s ", p->junction[i].room_name);
	// }
	// ft_printf("\n");
	// i = p->size;
	// while (--i >= 0)
	// {
	// 	ft_printf("%s  ", p->junction[i].room_name);
	// 	j = p->size;
	// 	while (--j >= 0)
	// 	{
	// 		if (i == j)
	// 			ft_printf("  ");
	// 		else if (p->matrix[i][j] == 0)
	// 			ft_printf(". ");
	// 		else if (p->matrix[i][j] == __INT_MAX__)
	// 			ft_printf("X ");
	// 		else
	// 			ft_printf("%d ", p->matrix[i][j]);
	// 	}
	// 	ft_printf("    %d\n", bfs->matrix_level[i]);
	// }
 

	// ft_printf("max_path: %d\n", bfs->max_path);

	// bfs->path_id = -1;	
	// while (++bfs->path_id < bfs->max_path)
	// {
	// 	i = -1;
	// 	while (++i < p->size)
	// 		bfs->tmp_path[i] = -1;
	// 	find_path(bfs, p, p->data.rooms.end_index, 0);
 	// 	bfs_new_node(bfs->tmp_path, &bfs->path, p->size);
	// }

	find_path(bfs, p, p->data.rooms.end_index, 0);
	ft_printf("\n");
	i = -1;
	while (++i < p->size && bfs->tmp_path[i] > 0)
	{
		ft_printf("<<<>>>>   %s ", p->junction[bfs->tmp_path[i]].room_name);
		ft_printf(" %d\n", bfs->tmp_path[i]);
	}
	// t_path	*cpy;

	// cpy = bfs->path;

	// bfs->path_id = -1;
	// while (++bfs->path_id < bfs->max_path && cpy)
	// {
	// 	i = -1;
	// 	while (++i < p->size)
	// 	{
	// 		if (cpy->data[i] != -1)
	// 		{
	// 			ft_printf("Chemin #%d: ", bfs->path_id + 1);
	// 			ft_printf("%s ", p->junction[cpy->data[i]].room_name);
	// 			ft_printf(" %d\n", cpy->data[i]);
	// 		}
	// 	}
	// 	cpy = cpy->next;
	// }

	


	// int i = p->size;
	// //bfs->path = rev(bfs->path, p->size);
	// while (--i > -1)
	// {
		// ft_printf("%s\n", p->junction[bfs->path[i]].room_name);
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