/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tubes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 01:32:13 by cseguier          #+#    #+#             */
/*   Updated: 2020/02/27 05:29:46 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

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
	static int	i = 0;

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

int	**handle_tubes(char **line, t_list **tubes, t_hthandle *t_hthandler, int room_count, char **storage)
{
	int **matrix;

	if (!(matrix = allocate_double_array(room_count)))
		exit_error("Malloc failed\n", (char*)__func__);
	if (!fill_adjacency_matrix(matrix, *line, t_hthandler))
		return (NULL);
	while (ft_get_line(0, line, storage) > 0)
	{
		if (!(add_front_node(tubes, *line)))
			return (0);
		if (is_empty(*line))
			return (NULL);
		else if (is_command(*line))
			return (NULL);
		else if (is_comment(*line))
			continue;
		if (is_line_valid(*line))
			if (!fill_adjacency_matrix(matrix, *line, t_hthandler))
				return (NULL);
	}
	return (matrix);
}
