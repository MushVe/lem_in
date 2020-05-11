/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 18:15:59 by cseguier          #+#    #+#             */
/*   Updated: 2020/04/24 18:40:10 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

void	go_to_next(t_combo_data *cd, t_ant_status *ant, t_bada_ids id)
{
	cd->path_combo[id.path].room[id.room + 1].ant = id.ant;
	ant[id.ant].id_path = id.path;
	ant[id.ant].id_room = cd->path_combo[id.path].room[id.room + 1].id;
	cd->path_combo[id.path].room[id.room].ant = -1;
}
