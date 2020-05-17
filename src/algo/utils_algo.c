/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_algo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 05:52:29 by cseguier          #+#    #+#             */
/*   Updated: 2020/03/12 16:53:58 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

void	bfs_free_all(t_bfs *bfs)
{
	ft_memdel((void*)&bfs->visited_record);
	ft_memdel((void*)&bfs->parent);
	ft_memdel((void*)&bfs->tmp_path);
	ft_memdel((void*)&bfs->matrix_level);
}

void	reset_visited(t_p *p, t_bfs *bfs)
{
	int	i;

	i = -1;
	while (++i < p->size)
		bfs->visited_record[i] = 0;
}

static void visited(t_bfs *bfs, int size)
{
	if (!(bfs->visited_record = ft_memalloc(sizeof(int) * size)))
		exit_error("Malloc Failed", (char*)__func__);
}
static void parent(t_bfs *bfs, int size)
{
	if (!(bfs->parent = ft_memalloc(sizeof(int) * size)))
		exit_error("Malloc Failed", (char*)__func__);
}
static void tmp_path(t_bfs *bfs, int size)
{
	if (!(bfs->tmp_path = ft_memalloc(sizeof(int) * size)))
		exit_error("Malloc Failed", (char*)__func__);
}
static void rooms(t_bfs *bfs, int size)
{
	if (!(bfs->rooms = ft_memalloc(sizeof(t_room_infos) * size)))
		exit_error("Malloc Failed", (char*)__func__);
}
static void matrix_level(t_bfs *bfs, int size)
{
	if (!(bfs->matrix_level = ft_memalloc(sizeof(int) * size)))
		exit_error("Malloc Failed", (char*)__func__);
}


void	bfs_init(t_bfs *bfs, int size)
{
	int	i;

	visited(bfs, size);
	parent(bfs, size);
	tmp_path(bfs, size);
	rooms(bfs, size);
	matrix_level(bfs, size);

	i = -1;
	while (++i < size)
		bfs->tmp_path[i] = -1;
	bfs->final_score = 0;
	bfs->max_path = 0;
	bfs->path_nb = 0;
	bfs->path_list = NULL;
}

void	get_matrix_level(t_p *p, t_bfs *bfs)
{
	int	i;
	int	j;

	i = -1;
	while (++i < p->size)
	{
		j = -1;
		while (++j < p->size)
			if (p->matrix[i][j] > 0)
				bfs->matrix_level[i] = p->matrix[i][j];
	}
}

void	fill_path_array(t_bfs *bfs)
{
	t_path_list	*cpy;
	int			room_id;
	int			path_id;

	if (!(bfs->path_array = ft_memalloc(sizeof(t_path_array) * bfs->path_nb)))
		exit_error("Malloc Failed", (char*)__func__);
	cpy = bfs->path_list;
	path_id = -1;
	while (cpy)
	{
		if (!(bfs->path_array[++path_id].room = \
			ft_memalloc(sizeof(int) * cpy->size)))
			exit_error("Malloc Failed", (char*)__func__);
		room_id = -1;
		while (++room_id < cpy->size)
			bfs->path_array[path_id].room[room_id] = cpy->room[room_id];
		bfs->path_array[path_id].size = cpy->size;
		cpy = cpy->next;
	}
}

/*
** void	print_path_array(t_p *p, t_bfs *bfs)
** {
** 	int	room_id;
** 	int	path_id;
** 	int	id_alias;
**
** 	path_id = -1;
** 	while (++path_id < bfs->path_nb)
** 	{
** 		ft_printf("\n+++ PATH #%d OF %d ROOMS +++\n", \
** 			path_id, bfs->path_array[path_id].size);
** 		room_id = -1;
** 		while (++room_id < bfs->path_array[path_id].size)
** 		{
** 			id_alias = bfs->path_array[path_id].room[room_id];
** 			//ft_printf(" id. %6d", bfs->path_array[path_id].room[room_id]);
** 			ft_printf(" - [%s]", p->junction[id_alias].room_name);
** 		}
** 		ft_printf("\n");
** 	}
** 	ft_printf("\n");
** }
**
** void	print_path_list(t_p *p, t_bfs *bfs)
** {
** 	t_path_list	*cpy;
** 	int			i;
**
** 	cpy = bfs->path_list;
** 	bfs->path_id = 0;
** 	while (cpy && ++bfs->path_id)
** 	{
**		ft_printf("<LIST> PATH #%d OF %d ROOMS <LIST>\n", \
**			bfs->path_id, cpy->size);
** 		i = -1;
** 		while (++i < cpy->size)
** 		{
** 			ft_printf(" id_%d", cpy->room[i]);
** 			ft_printf(" [%s]\n", p->junction[cpy->room[i]].room_name);
** 		}
** 		ft_printf("++++++++++++++++++\n");
** 		cpy = cpy->next;
** 	}
** }
**
**
** void	print_matrix(t_p *p, t_bfs *bfs, int i, int j)
** {
** 	ft_printf("   ");
** 	i = p->size;
** 	while (--i >= 0)
** 		ft_printf("%s ", p->junction[i].room_name);
** 	ft_printf("\n");
** 	i = p->size;
** 	while (--i >= 0)
** 	{
** 		ft_printf("%s  ", p->junction[i].room_name);
** 		j = p->size;
** 		while (--j >= 0)
** 		{
** 			if (i == j)
** 				ft_printf("  ");
** 			else if (p->matrix[i][j] == 0)
** 				ft_printf(". ");
** 			else if (p->matrix[i][j] == __INT_MAX__)
** 				ft_printf("X ");
** 			else
** 				ft_printf("%d ", p->matrix[i][j]);
** 		}
** 		ft_printf("    %d\n", bfs->matrix_level[i]);
** 	}
** }
*/
