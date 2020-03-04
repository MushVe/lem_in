/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 05:18:48 by cseguier          #+#    #+#             */
/*   Updated: 2020/03/04 05:49:03 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	bfs_free_list(t_path **path)
{
	t_path	*cpy;
	t_path	*tmp;

	cpy = *path;
	tmp = NULL;
	while (cpy)
	{
		tmp = cpy->next;
		ft_memdel((void*)&cpy->data);
		ft_memdel((void*)&cpy);
		cpy = NULL;
		cpy = tmp;
	}
}

int		bfs_new_node(int *data, t_path **path, int size)
{
	t_path	*cpy;
	t_path	*node;
	int		i;
	int		j;

	cpy = *path;
	if (!(node = (t_path*)ft_memalloc(sizeof(t_path))) 
		|| !(node->data = ft_memalloc(sizeof(int) * size)))
		exit_error("Malloc Failed", (char*)__func__);
	i = size;
	j = -1;
	while (--i >= 0)
		node->data[i] = data[++j];
	node->next = NULL;
	if (!cpy)
	{
		*path = node;
		return (1);
	}
	while (cpy->next != NULL)
	{
		cpy = cpy->next;
	}
	cpy->next = node;
	return (1);
}

int		*bfs_get_node(int aim, t_path *path)
{
	t_path	*cpy;
	int		i;

	cpy = path;
	i = -1;
	while (++i < aim && cpy)
		cpy = cpy->next;
	return (cpy->data);
}
