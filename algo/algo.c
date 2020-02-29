/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 01:27:16 by cseguier          #+#    #+#             */
/*   Updated: 2020/02/29 08:15:03 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int algo(t_p *p)
{
	t_queue	*q;
	int		host;
	int		link;
	char	*visited_record;

	if (!(visited_record = ft_memalloc(sizeof(char*) * p->size + 1)))
		exit_error("Malloc Failed", (char*)__func__);
	q = create_queue();
	host = p->data.rooms.start_index;
	ft_printf("000 %s\t%d\n", p->junction[host].room_name, p->junction[host].index);
	ft_printf("host %d %d\n", host, p->data.rooms.start_index);
	en_queue(q, p->junction[host].index);
	visited_record[host] = 1;


	while (q->rear != NULL && host != p->data.rooms.end_index)
	{
		host = q->front->data;
		de_queue(q);
		ft_printf("111 %s\t%d\n", p->junction[host].room_name, p->junction[host].index);
		link = -1;
		while (++link < p->size)
		{
			if (p->matrix[host][link] == 1 && visited_record[link] == 0)
			{
				en_queue(q, p->junction[link].index);
				visited_record[link] = 1;
			}
		}
	}




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
	// while(!isempty)
	// {
	// 	// Dequeue a vertex from queue and print it
	// 	s = queue.front();
	// 	cout << s << " ";
	// 	queue.pop_front();
  
	// 	// Get all adjacent vertices of the dequeued
	// 	// vertex s. If a adjacent has not been visited,
	// 	// then mark it visited and enqueue it
	// 	for (i = adj[s].begin();i != adj[s].end();++i)
	// 	{
	// 		if (!visited[*i])
	// 		{
	// 			visited[*i] = true;
	// 			queue.push_back(*i);
	// 		}
	// 	}
	// }