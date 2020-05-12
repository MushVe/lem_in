/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 06:45:19 by cseguier          #+#    #+#             */
/*   Updated: 2020/03/06 06:45:34 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

void	exit_error(char *reason, char *camefrom)
{
	ft_printf("In function <%s> : %s\n", camefrom, reason);
	exit(0);
}

int		white_space_count(char *line)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (line[++i])
		count += line[i] == ' ';
	return (count);
}
