/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 09:46:07 by cseguier          #+#    #+#             */
/*   Updated: 2020/06/24 09:48:55 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

void		get_start_values(t_combo_data *cd, t_combo_utils *u)
{
	u->best_behind = 0;
	u->first_path = u->test_id - 1;
	u->path_id = -1;
	cd->nb_line = 0;
	clear_path_combo(cd->path_combo, u->test_limit);
	cd->nb_path = 0;
}

static int	find_target(t_path_combo *path, int nb_path, int marge)
{
	int	i;
	int	target_max;
	int	target_min;

	i = -1;
	target_max = 0;
	target_min = 0;
	while (++i < nb_path)
	{
		if (path[i].ants + path[i].size < path[target_max].ants +\
			path[target_max].size)
			target_max = i;
		if (path[i].ants + path[i].size > path[target_min].ants +\
			path[target_min].size)
			target_min = i;
	}
	if (marge < 0)
		return (target_max);
	return (target_min);
}

static void print_path_combo(t_path_combo *path, int nb_path)
{
	int	i;
	int	j;

	i = -1;
	while (++i < nb_path)
	{
		j = -1;
		ft_printf("--- PATH #%d ---\n", i + 1);
		ft_printf("ants: %d\n", path[i].ants);
		ft_printf("size: %d\n", path[i].size);
		while (++j < path[i].size)
		{
			ft_printf("-> ROOM #%d\t", j + 1);
		//	ft_printf("ants (%d)\t", path[i].room[j].ant);
			ft_printf("id [%d]\n", path[i].room[j].id);
		}
		ft_printf("\n");
	}
	ft_printf("                                      ");
}

static int	is_ant_negative(t_path_combo *path, int nb_path)
{
	int	i;

	i = -1;
	while (++i < nb_path)
		if (path[i].ants < 0)
			return (1);
	return (0);
}

static int	adjust_ants(t_path_combo *path, int nb_path, int marge, int lines)
{
	int	op;
	int	target;

	// ft_printf("\n ---- adjust ants\n");
	op = (marge < 0) ? 1 : -1;
	while (marge != 0)
	{
		target = find_target(path, nb_path, marge);
		path[target].ants += op;
		marge += op;
		if (path[target].ants + path[target].size - 2 != lines)
			lines += op;
	}
	if (is_ant_negative(path, nb_path))
		return (__INT_MAX__);
	// print_path_combo(path, nb_path);
	return (lines);
}

int			lead_ants(t_path_combo *path, int ants, int nb_path)
{
	int	lines;
	int	i;
	int total_ants;

	// ft_printf("---------------------------------- lead ants : ");
	lines = 0;
	i = -1;
	total_ants = 0;
	while (++i < nb_path)
		lines += (ants / nb_path) + path[i].size - 2;
	lines = ft_round(lines, nb_path);
	i = -1;
	while (++i < nb_path)
		path[i].ants = lines - (path[i].size - 2);
	i = -1;
	while (++i < nb_path)
		total_ants += path[i].ants;
	// ft_printf("[%d]", lines);
	if (total_ants != ants)
		lines = adjust_ants(path, nb_path, total_ants - ants, lines);
	// ft_printf(" > [%d]\n", lines);
	return (lines);
}
