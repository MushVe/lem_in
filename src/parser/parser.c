/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 01:31:58 by cseguier          #+#    #+#             */
/*   Updated: 2020/05/20 17:28:50 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

/*
** Possibles erreurs dans le parsing des rooms
** alors, est-ce qu'on considere que si la salle recue
** ne contient pas de coordonnées x,y c'est une erreur et on arrete le parsing ?
** est-ce que deux commandes a la suite est un motif d'arret du parsing
** est-ce que le start et end sont reassignable ?
** #######
** Steps:
** 1/ Get the ants_count return_ants()
** Verify Pitfalls
** if No error => Proceed
** 2/Get the rooms
** Verify Pitfalls
*/

void			delete_junction_table(t_map_room_index *junction)
{
	free(junction);
}

void			delete_display_list(t_list *list)
{
	t_list *next;

	next = NULL;
	while (list)
	{
		next = list->next;
		free(list->data);
		free(list);
		list = next;
	}
}

/*
** display
*/

void			display_anthill(t_list *list)
{
	if (list != NULL)
		display_anthill(list->next);
	if (list)
		ft_printf("%s\n", list->data);
}

void			display(t_anthill data, t_list *list)
{
	ft_printf("%lld\n%s\n", data.ant_count, list->data);
	display_anthill(list->next);
}

/*
** Return the matrix storing the connections
** between the lines
** Pas sur,
** if (!(handle_tubes(p)))
** 	exit_error("ERROR, tubes parsing failed\n", (char*)__func__);
** voir si on a assez de data pour faire le traiteme, (char*)__func__nt
*/

int				parser(t_p *p)
{
	char *line;

	line = NULL;
	handle_ants(p);
	if (!handle_rooms(&line, &p->tmp, &p->data))
		exit_error("ERROR, room parsing failed\n", (char*)__func__);
	hash_table_create(p->data.room_count, &p->hthandler);
	p->junction = store_rooms(&p->data, &p->hthandler, p->tmp);
	if (!(handle_tubes(p, &line)))
		exit_error("ERROR, tubes parsing failed\n", (char*)__func__);
	p->size = p->data.room_count;
	return (0);
}
