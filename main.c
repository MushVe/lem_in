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
	t_p p;

	init(&p);
	parser(&p);
	// display(p.data, p.tmp);
	algo(&p);

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