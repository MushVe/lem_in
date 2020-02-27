/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tubes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 01:32:17 by cseguier          #+#    #+#             */
/*   Updated: 2020/02/27 05:55:11 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_ht	*does_room_exist(char *line, t_hthandle *t_hthandler)
{
	char	*room;

	room = split_tubes(line);
	return (hash_table_get(t_hthandler, room));
}

int		is_tube_valid(t_ht **room1, t_ht **room2, char *line, t_hthandle *t_hthandler)
{
	*room1 = does_room_exist(line, t_hthandler);
	*room2 = does_room_exist(line, t_hthandler);
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
	static int	index = 0;
	int			offset;

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
