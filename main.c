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

void	init(t_p *p, t_bfs *bfs)
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

void		clean(t_p *p)
{
	delete_display_list(p->tmp);
	hash_table_delete(&p->hthandler);
	delete_junction_table(p->junction);
	free(p->data.rooms.end);
	free(p->data.rooms.start);
	free(p->storage);
}

int			 main()
{
	t_p 			p;
	t_bfs			bfs;
	t_combo_data	cd;

	ft_printf("+ init\n");
	init(&p, &bfs);
	ft_printf("+ parser\n");
	parser(&p);
	ft_printf("+ algo\n");
	// display(p.data, p.tmp);
	algo(&p, &bfs);
	ft_printf("+ resolve\n");
	resolve(&p, &bfs, &cd);
	ft_printf("+ print\n");
	print_lem_in(&cd);


	// for (size_t i = 0; i < p.size; i++)
	// {
	// 	for (size_t j = 0; j < p.size; j++)
	// 	{
	// 		if (p.matrix[i][j] != 1)
	// 			ft_printf(".");
	// 		else
	// 			ft_printf("1");
	// 	}
	// 	ft_printf("\n");
	// }

	/*
	** Attention a ne pas utiliser avant la fin du programme hein
	*/
	clean(&p);
	ft_doublefree_int(p.matrix, p.size);
}