/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 17:54:29 by cseguier          #+#    #+#             */
/*   Updated: 2019/11/20 22:35:23 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

static void	gnl_free_function(t_gnl_lst **begin, t_gnl_lst *current)
{
	t_gnl_lst	*tmp;

	if (current == *begin)
		*begin = current->next;
	else
	{
		tmp = *begin;
		while (tmp->next != current)
			tmp = tmp->next;
		tmp->next = tmp->next->next;
	}
	free(current->stock);
	free(current);
}

static int	gnl_ret_functions(t_gnl_lst **begin, t_gnl_lst *lst, int ret)
{
	char	buff[GNL_BUFFER_SIZE + 1];

	if (ret == 0)
	{
		if (lst->stock != NULL)
			return (1);
	}
	else
	{
		if (lst->stock)
			return (1);
		if ((ret = read(lst->fd, buff, GNL_BUFFER_SIZE)) == -1)
			return (-1);
		buff[ret] = 0;
		if (ret > 0)
		{
			if (!(lst->stock = gnl_strjoinf(lst->stock, buff)))
				return (-1);
			return (1);
		}
	}
	gnl_free_function(begin, lst);
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static t_gnl_lst	*lst = NULL;
	t_gnl_lst			*current;
	int					ret;

	if (fd < 0 || !line || GNL_BUFFER_SIZE < 1)
		return (-1);
	if (!(current = gnl_get_elem(&lst, fd)))
		return (-1);
	if ((ret = gnl_read(current)) == -1)
		return (-1);
	if (current->stock)
	{
		if (!(gnl_fill_line(current, line)))
			return (-1);
	}
	else
	{
		if (!(*line = ft_memalloc(1)))
			return (-1);
	}
	return (gnl_ret_functions(&lst, current, ret));
}
