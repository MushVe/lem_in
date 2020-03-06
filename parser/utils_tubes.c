/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tubes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 01:32:17 by cseguier          #+#    #+#             */
/*   Updated: 2020/03/06 06:37:54 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_ht	*does_room_exist(char *line, t_hthandle *ht)
{
	char	*room;

	room = split_tubes(line);
	return (hash_table_get(ht, room));
}

int		is_tube_valid(t_ht **r1, t_ht **r2, char *line, t_hthandle *ht)
{
	*r1 = does_room_exist(line, ht);
	*r2 = does_room_exist(line, ht);
	if (*r1 && *r2)
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
