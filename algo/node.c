/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 05:18:48 by cseguier          #+#    #+#             */
/*   Updated: 2020/03/07 05:51:29 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	bfs_free_list(t_path_list **path)
{
	t_path_list	*cpy;
	t_path_list	*tmp;

	cpy = *path;
	tmp = NULL;
	while (cpy)
	{
		tmp = cpy->next;
		ft_memdel((void*)&cpy->room);
		ft_memdel((void*)&cpy);
		cpy = NULL;
		cpy = tmp;
	}
}

int		bfs_new_node(int *room, t_path_list **path, int size)
{
	t_path_list	*cpy;
	t_path_list	*node;
	int			i;
	int			j;

	cpy = *path;
	if (!(node = (t_path_list*)ft_memalloc(sizeof(t_path_list)))
		|| !(node->room = ft_memalloc(sizeof(int) * size)))
		exit_error("Malloc Failed", (char*)__func__);
	i = size;
	j = -1;
	while (room[++j] != -1)
		node->room[--i] = room[j];
	node->size = size;
	node->next = NULL;
	if (!cpy)
	{
		*path = node;
		return (1);
	}
	while (cpy->next != NULL)
		cpy = cpy->next;
	cpy->next = node;
	return (1);
}

int		*bfs_get_node(int aim, t_path_list *path)
{
	t_path_list	*cpy;
	int			i;

	cpy = path;
	i = -1;
	while (++i < aim && cpy)
		cpy = cpy->next;
	return (cpy->room);
}
