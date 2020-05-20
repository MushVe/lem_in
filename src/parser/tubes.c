/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tubes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 01:32:13 by cseguier          #+#    #+#             */
/*   Updated: 2020/05/20 17:18:00 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

int	is_line_valid(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (line[i] == '-')
			return (1);
	return (0);
}

int	fill_adjacency_matrix(int **matrix, char *line, t_hthandle *t_hthandler)
{
	t_ht		*room1;
	t_ht		*room2;

	room1 = NULL;
	room2 = NULL;
	if (is_tube_valid(&room1, &room2, line, t_hthandler))
	{
		matrix[room1->index][room2->index] = 1;
		matrix[room2->index][room1->index] = 1;
		return (1);
	}
	return (0);
}

int	handle_tubes(t_p *p, char **line)
{
	if (!(p->matrix = allocate_double_array(p->data.room_count)))
		exit_error("Malloc failed\n", (char*)__func__);
	if (!fill_adjacency_matrix(p->matrix, *line, &p->hthandler))
		return (1);
	while (get_next_line(0, line) > 0)
	{
		if (!(add_front_node(&p->tmp, *line)))
			return (1);
		if (is_empty(*line))
			return (1);
		else if (is_command(*line))
			return (1);
		else if (is_comment(*line))
			continue;
		if (is_line_valid(*line))
		{
			if (!fill_adjacency_matrix(p->matrix, *line, &p->hthandler))
				return (1);
		}
		else
			return (1);
	}
	return (1);
}
