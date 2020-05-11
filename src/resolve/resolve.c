/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 09:46:07 by cseguier          #+#    #+#             */
/*   Updated: 2020/04/24 18:39:52 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

static void		add_new_path(t_bfs *bfs, t_combo_data *cd, t_combo_utils *u)
{
	if (bfs->path_array[u->first_path].size > u->best_nb_lines)
		u->best_behind = 1;
	copy_path(bfs, cd->path_combo, u->first_path, ++u->path_id);
	cd->nb_line = lead_ants(cd->path_combo, u->nb_total_ants, cd->nb_path);
	if (cd->nb_line < u->best_nb_lines)
	{
		u->best_nb_path = cd->nb_path;
		u->best_nb_lines = cd->nb_line;
		clear_path_combo(u->best_combo, u->test_limit);
		copy_path_combo(u->best_combo, cd->path_combo, cd->nb_path);
	}
}

static int		get_next_path(t_bfs *bfs, int path_id)
{
	if (path_id + 1 < bfs->path_nb)
		return (path_id + 1);
	return (-1);
}

static void		process_paths(t_bfs *bfs, t_combo_data *cd, t_combo_utils *u)
{
	while (++u->test_id < bfs->path_nb)
	{
		get_start_values(cd, u);
		while (++cd->nb_path <= u->test_limit && !u->best_behind)
		{
			u->first_path = get_next_path(bfs, u->first_path);
			if (u->first_path == -1)
			{
				cd->nb_path--;
				if (u->test_id < u->test_limit)
					u->minimum_size++;
				break ;
			}
			else if (!(collide(bfs, cd->path_combo, u->first_path)))
				add_new_path(bfs, cd, u);
			else
				cd->nb_path--;
		}
	}
}

static int		get_shortest_combo(t_p *p, t_bfs *bfs, t_combo_data *cd)
{
	t_combo_utils	u;

	init_utils(p, cd, &u);
	init_combo(&cd->path_combo, u.test_limit);
	init_combo(&u.best_combo, u.test_limit);
	process_paths(bfs, cd, &u);
	clear_path_combo(cd->path_combo, u.test_limit);
	copy_path_combo(cd->path_combo, u.best_combo, u.best_nb_path);
	free_path_combo(u.best_combo, u.best_nb_path);
	cd->nb_line = u.best_nb_lines;
	cd->nb_path = u.best_nb_path;
	return (0);
}

t_path_combo	*resolve(t_p *p, t_bfs *bfs, t_combo_data *cd)
{
	quicksort(bfs);
	get_shortest_combo(p, bfs, cd);
	return (0);
}
