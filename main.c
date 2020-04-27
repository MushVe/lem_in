/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 21:35:49 by cseguier          #+#    #+#             */
/*   Updated: 2020/04/21 21:35:49 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

void	init(t_p *p)
{
	p->tmp = NULL;
	p->size = 0;
	p->line = NULL;
	p->storage = NULL;
	p->data.ant_count = 0;
	p->data.room_count = 0;
	p->data.rooms.end = NULL;
	p->data.rooms.start = NULL;
	p->hthandler.capacity = 0;
	p->hthandler.current_capacity = 0;
	p->hthandler.hash_table = NULL;
	p->hthandler.modulo = 0;
}

void	clean(t_p *p, t_bfs *bfs, t_combo_data *cd)
{
	int	i;

	delete_display_list(p->tmp);
	hash_table_delete(&p->hthandler);
	delete_junction_table(p->junction);
	free(p->data.rooms.end);
	free(p->data.rooms.start);
	free(p->storage);
	i = -1;
	while (++i < bfs->path_nb)
		ft_memdel((void*)&bfs->path_array[i].room);
	ft_memdel((void*)&bfs->path_array);
	i = -1;
	while (++i < cd->nb_path)
		ft_memdel((void*)&cd->path_combo[i].room);
	ft_memdel((void*)&cd->path_combo);
}

int		main(void)
{
	t_p				p;
	t_bfs			bfs;
	t_combo_data	cd;

	init(&p);
	parser(&p);
	display(p.data, p.tmp);
	algo(&p, &bfs);
	resolve(&p, &bfs, &cd);
	print_lem_in(&p, &cd);
	clean(&p, &bfs, &cd);
	ft_doublefree_int(p.matrix, p.size);
}
