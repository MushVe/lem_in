/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 05:42:07 by cseguier          #+#    #+#             */
/*   Updated: 2020/03/06 05:45:05 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*my_strtok(char *line, int *end)
{
	static int	index = 0;
	int			offset;

	if (index != 0)
		index++;
	offset = index;
	while (line[index])
	{
		if (line[index] == '\n')
		{
			line[index] = '\0';
			return (line + offset);
		}
		index++;
	}
	index = 0;
	*end = 0;
	return (line + offset);
}
