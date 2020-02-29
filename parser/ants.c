/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 01:30:39 by cseguier          #+#    #+#             */
/*   Updated: 2020/02/29 07:17:00 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		is_ant_count_valid(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (!ft_isdigit(line[i]))
			exit_error("Ants parsing invalid\n", (char*)__func__);
	return (atoi(line));
}

void	get_ants(t_p *p)
{
	p->data.ant_count = is_ant_count_valid(p->line);
}

void	handle_ants(t_p *p)
{
	if (ft_get_line(0, &p->line, &p->storage) < 0)
		exit_error("GNL error\n", (char*)__func__);
	if (p->line)
		get_ants(p);
	else
	{
		exit_error("line empty\n", (char*)__func__);
		exit(0);
	}
}
