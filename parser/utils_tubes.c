/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tubes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 01:32:17 by cseguier          #+#    #+#             */
/*   Updated: 2020/02/26 03:56:20 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

h_t		*does_room_exist(char *line, h_t_handle *h_t_handler)
{
	char	*room;

	room = split_tubes(line);
	return (hash_table_get(h_t_handler, room));
}

int		is_tube_valid(h_t **room1, h_t **room2, char *line, h_t_handle *h_t_handler)
{
	*room1 = does_room_exist(line, h_t_handler);
	*room2 = does_room_exist(line, h_t_handler);
	if (*room1 && *room2)
		return (1);
	return (0);
}

/*
** This function try to mimic strtok
** so it keeps track of the last call with a static
** and replace the character '-' by 0
** so it let me split the string easily
*/

char	*split_tubes(char *line)
{
	static int	index;
	int			offset;

	index = 0;
	if (index != 0)
	{
		line[index] = '-';
		index++;
	}
	offset = index;
	while (line[index])
	{
		if (line[index] == '-')
		{
			line[index] = '\0';
			return (line);
		}
		index++;
	}
	index = 0;
	return (line + offset);
}
