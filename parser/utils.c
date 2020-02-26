/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 01:32:22 by cseguier          #+#    #+#             */
/*   Updated: 2020/02/26 03:57:26 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	exit_error(char *reason, char *camefrom)
{
	ft_printf("In function <%s> : %s\n", camefrom, reason);
	exit(0);
}

int		is_comment(char *line)
{
	return (line[0] == '#') && (line[1] && line[1] != '#');
}

int		is_command(char *line)
{
	return (line[0] == '#') && (line[1] && line[1] == '#');
}

/*
** Pas de problemes de leaks, juste une reference a Line
*/

int		is_command_valid(char *line, char **to_store)
{
	int	ret;

	if (*to_store != NULL)
		exit(0);
	ret = ft_strcmp(line, "##start") == 0 || ft_strcmp(line, "##end") == 0;
	if (ret)
		*to_store = line + 2;
	return (ret);
}

int		is_empty(char *line)
{
	return (line && ft_strlen(line) <= 0 && line[0] != '\n');
}

/*
** Attention danger
** Si dans la boucle on ne peux pas allouer on risque de leaks
** car on ne pourra pas free ce qui a ete alloue avant
*/

int		**allocate_double_array(int size)
{
	int	i;
	int	**array;

	i = -1;
	if (!(array = ft_memalloc(sizeof(int*) * size)))
		return (NULL);
	while (++i < size)
		if (!(array[i] = ft_memalloc(sizeof(int*) * size)))
			return (NULL);
	return (array);
}
