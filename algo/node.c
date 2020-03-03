/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 05:18:48 by cseguier          #+#    #+#             */
/*   Updated: 2020/03/03 05:30:41 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	bfs_free_list(t_path **list)
{
	t_path	*cpy;
	t_path	*tmp;

	cpy = *list;
	tmp = NULL;
	while (cpy)
	{
		tmp = cpy->next;
		ft_memdel((void*)&cpy->str);
		ft_memdel((void*)&cpy);
		cpy = NULL;
		cpy = tmp;
	}
}

int		bfs_new_node(int *data, int size, t_pf *p)
{
	t_path	*cpy;
	t_path	*node;

	cpy = p->first;
	if (!(node = (t_path*)ft_memalloc(sizeof(t_path))))
		return (0);
	node->str = ft_strdup(data);
	ft_memdel((void*)&data);
	node->size = size;
	if (p->null == 1)
		node->null = 1;
	else
		node->null = 0;
	node->next = NULL;
	if (!cpy)
	{
		p->first = node;
		return (1);
	}
	while (cpy->next != NULL)
		cpy = cpy->next;
	cpy->next = node;
	return (1);
}

char	*bfs_get_node(int aim, t_pf *p)
{
	t_path	*cpy;
	int		i;

	cpy = p->first;
	i = -1;
	while (++i < aim && cpy)
		cpy = cpy->next;
	return (cpy->str);
}