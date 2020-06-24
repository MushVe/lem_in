/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 17:52:34 by cseguier          #+#    #+#             */
/*   Updated: 2020/06/24 09:57:36 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

static void	init_ant_status(t_ant_status **ant, int count)
{
	int	i;

	if (!(*ant = ft_memalloc(sizeof(t_ant_status) * count)))
		exit_error("Malloc Failed", (char*)__func__);
	i = -1;
	while (++i < count)
	{
		(*ant)[i].id_path = -1;
		(*ant)[i].id_room = -1;
	}
}

static void	bada_ants(t_combo_data *cd, t_ant_status *ant)
{
	t_bada_ids id;

	id.path = -1;
	while (++id.path < cd->nb_path)
	{
		id.room = cd->path_combo[id.path].size;
		while (--id.room >= 0)
		{
			id.ant = cd->path_combo[id.path].room[id.room].ant;
			if (id.ant != -1)
			{
				if ((id.room + 1) >= cd->path_combo[id.path].size)
				{
					ant[id.ant].id_path = -2;
					ant[id.ant].id_room = -2;
				}
				else
					go_to_next(cd, ant, id);
			}
		}
	}
}

static int	affect_ants(t_combo_data *cd, t_ant_status *ant, int id_ant, int max_ants)
{
	int	id_path;

	id_path = -1;
	while (++id_path < cd->nb_path)
	{
		if (cd->path_combo[id_path].ants > 0 && id_ant < max_ants)
		{
			cd->path_combo[id_path].room[1].ant = id_ant;
			ant[id_ant].id_path = id_path;
			ant[id_ant].id_room = cd->path_combo[id_path].room[1].id;
			cd->path_combo[id_path].ants--;
			id_ant++;
		}
	}
	return (id_ant);
}

static void	print_ants(t_p *p, t_ant_status *ant)
{
	int	i;
	int	check;

	check = 0;
	i = -1;
	while (++i < p->data.ant_count)
	{
		if (ant[i].id_room >= 0 && ant[i].id_room != p->data.rooms.start_index)
		{
			ft_printf("L%d-%s ", i + 1, p->junction[ant[i].id_room].room_name);
			check++;
		}
	}
	if (check)
		ft_printf("\n");
}

int			print_lem_in(t_p *p, t_combo_data *cd)
{
	t_ant_status	*ant;
	int				i;
	int				id_ant;

	init_ant_status(&ant, p->data.ant_count);
	i = -1;
	id_ant = 0;
	ft_printf("                                      [%d]\n", cd->nb_line);
	while (++i <= cd->nb_line)
	{
		bada_ants(cd, ant);
		id_ant = affect_ants(cd, ant, id_ant, p->data.ant_count);
		//print_ants(p, ant);
	}
	// ft_printf("Done \n");
	ft_memdel((void*)&ant);
	return (0);
}
