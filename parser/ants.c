/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 01:30:39 by cseguier          #+#    #+#             */
/*   Updated: 2020/02/26 02:09:57 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		is_ant_count_valid(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (!ft_isdigit(line[i]))
			return (0);
	return (atoi(line));
}

void	get_ants(char *line, t_anthill *data)
{
	int	ant_count;

	ant_count = is_ant_count_valid(line);
	if (ant_count <= 0)
		exit_error("Ants parsing invalid\n", (char*)__func__);
	data->ant_count = ant_count;
}

void	handle_ants(char **line, t_anthill *data, char **storage)
{
	if (ft_get_line(0, line, storage) < 0)
		exit_error("GNL error\n", (char*)__func__);
	if (line)
		get_ants(*line, data);
	else
	{
		exit_error("line empty\n", (char*)__func__);
		exit(0);
	}
}
