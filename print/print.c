/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 21:35:49 by cseguier          #+#    #+#             */
/*   Updated: 2020/04/21 21:35:49 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	init_ant_status(t_ant_status **ant, int count)
{
	int	i;

	if (!(*ant = ft_memalloc(sizeof(t_ant_status) * count)))
		exit_error("Malloc Failed", (char*)__func__);
	i = -1;
	// ft_printf("++");
	while (++i < count)
	{
		(*ant)[i].id_path = -1;
		(*ant)[i].id_room = -1;
		// ft_printf(" {%d}", i);
	}
	// ft_printf("\n");
}

// combos (paths / rooms / nbfourmis dans path)
// nb line ?

// chaque tour faire avancer fourmis dans paths
// chaque tour envoyer x fourmis dans paths
// associer room status et ant status pour afficher
// afficher ant status

// -1 = start
// -2 = end

void	bada_ants(t_combo_data *cd, t_ant_status *ant, int end)
{
	int	id_path;
	int	id_room;
	int	id_ant;
	
	id_path = -1;
	while (++id_path < cd->nb_path)
	{
		// ft_printf("id_path [%d]\n", id_path);
		id_room = cd->path_combo[id_path].size;
		while (--id_room >= 0)
		{
			// ft_printf("\tid_room [%d]\n", id_room);
			id_ant = cd->path_combo[id_path].room[id_room].ant;
			
			if (id_ant != -1)
			{
				if ((id_room + 1) >= cd->path_combo[id_path].size)
				{
					ant[id_ant].id_path = -2;
					ant[id_ant].id_room = -2;
				}
				else
				{
					cd->path_combo[id_path].room[id_room + 1].ant = id_ant;
					ant[id_ant].id_path = id_path;
					ant[id_ant].id_room = cd->path_combo[id_path].room[id_room + 1].id;
					cd->path_combo[id_path].room[id_room].ant = -1;
				}
			}
		}
	}
}

int	affect_ants(t_combo_data *cd, t_ant_status *ant, int id_ant)
{
	int	id_path;

	id_path = -1;
	// ft_printf("---- Affect\n");
	// ft_printf("id_ant: %d\n", id_ant);
	while (++id_path < cd->nb_path)
	{
		// ft_printf("  id_path: %d\n", id_path);
		// ft_printf("   ANTS R U THERE: %d\n", cd->path_combo[id_path].ants);
		if (cd->path_combo[id_path].ants > 0)
		{
			// ft_printf("ant [%d] got in path [%d]\n", id_ant, id_path);
			cd->path_combo[id_path].room[0].ant = id_ant;
			ant[id_ant].id_path = id_path;
			ant[id_ant].id_room = cd->path_combo[id_path].room[0].id;
			cd->path_combo[id_path].ants--;
			id_ant++;
		}
	}
	return (id_ant);
}

void	print_ants(t_p *p, t_ant_status *ant)
{
	int	i;

	i = -1;
	//ft_printf("---- Print\n");
	while (++i < p->data.ant_count)
	{
		//ft_printf("\nid_ant: %d\n", i);
		//ft_printf("id_room: %d\n", ant[i].id_room);
		if (ant[i].id_room >= 0 && ant[i].id_room != p->data.rooms.start_index)
			ft_printf("L%d-%s ", i + 1, p->junction[ant[i].id_room].room_name);
	}
	ft_printf("\n");
}

int		print_lem_in(t_p *p, t_combo_data *cd)
{
	t_ant_status	*ant;
	int				i;
	int				id_ant;

	init_ant_status(&ant, p->data.ant_count);
	i = -1;
	id_ant = 0;
	while (++i <= cd->nb_line)
	{
		bada_ants(cd, ant, p->data.rooms.end_index);
		id_ant = affect_ants(cd, ant, id_ant);
		print_ants(p, ant);
	}
	return (0);
}





















/*
 * Cette fonction fait avancer les fourmis
 * c'est a dire elle parcours un tableau contenant
 * 
void fait_avancer_les_fourmis()

// care when ant_count < ants_by_round
void dunno(t_p *p, t_combo_data *cd)
{
	// int ant_count = p->data.ant_count;
	// int ants_by_round = cd->nb_path;
	// int current_ants_in = 0;
	// int ant_in_end = 0;
	// int i = 0;
	// int j = 0;
	// t_ant_status *ant;

	// while (ant_in_end < ant_count)
	// {
	// 	while (i < current_ants_in)
	// 	{
	// 		while (j < ants_by_round)
	// 		{
	// 			ant[i].id_room = cd->path_combo[j].room[i].id;
	// 		}
	// 		if (id_room == id_end)
	// 		{
	// 			ant_in_end++;
	// 		}
	// 	}
	// }
}*/