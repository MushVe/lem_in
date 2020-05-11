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

#include "../../includes/lem_in.h"

static int	is_ant_count_valid(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (!ft_isdigit(line[i]))
			exit_error("Ants parsing invalid\n", (char*)__func__);
	return (ft_atoi(line));
}

static void	get_ants(t_p *p)
{
	p->data.ant_count = is_ant_count_valid(p->new_line);
	if (p->data.ant_count <= 0)
		exit_error("Ants parsing invalid\n", (char*)__func__);
}

int			handle_ants(t_p *p)
{
	if (p->new_line)
		get_ants(p);
	return (1);
}
