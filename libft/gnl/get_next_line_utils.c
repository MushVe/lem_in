/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 17:57:00 by cseguier          #+#    #+#             */
/*   Updated: 2019/11/16 20:10:28 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char		*gnl_strjoinf(char *s1, char s2[GNL_BUFFER_SIZE])
{
	char	*new;
	int		size1;
	int		size2;

	size1 = 0;
	while (s1 && s1[size1])
		size1++;
	size2 = 0;
	while (s2[size2])
		size2++;
	if (!(new = (char *)ft_memalloc(sizeof(char) * (size1 + size2 + 1))))
		return (NULL);
	new[size1 + size2] = 0;
	size1 = 0;
	while (s1 && s1[size1])
	{
		new[size1] = s1[size1];
		size1++;
	}
	size2 = -1;
	while (s2[++size2])
		new[size1 + size2] = s2[size2];
	if (s1 != NULL)
		free(s1);
	return (new);
}

int			gnl_read(t_gnl_lst *lst)
{
	int		ret;
	char	buff[GNL_BUFFER_SIZE + 1];
	int		i;

	i = 0;
	while (i <= GNL_BUFFER_SIZE)
		buff[i++] = 0;
	while ((ret = read(lst->fd, buff, GNL_BUFFER_SIZE)) > 0)
	{
		buff[ret] = 0;
		if (!(lst->stock = gnl_strjoinf(lst->stock, buff)))
			return (-1);
		i = 0;
		while (i <= GNL_BUFFER_SIZE)
			buff[i++] = 0;
		i = -1;
		while (lst->stock[++i])
			if (lst->stock[i] == '\n')
				return (1);
	}
	return (ret);
}

t_gnl_lst		*gnl_get_elem(t_gnl_lst **lst, int fd)
{
	t_gnl_lst	*new;
	t_gnl_lst	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (tmp->fd == fd)
			return (tmp);
		tmp = tmp->next;
	}
	if (!(new = (t_gnl_lst *)ft_memalloc(sizeof(t_gnl_lst))))
		return (NULL);
	new->fd = fd;
	new->stock = NULL;
	new->next = NULL;
	if (!*lst)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (new);
}

int			gnl_fill_line(t_gnl_lst *lst, char **line)
{
	int		size;
	int		i;
	char	*tmp;

	size = 0;
	while (lst->stock[size] && lst->stock[size] != '\n')
		size++;
	if (!(*line = (char *)ft_memalloc(sizeof(char) * (size + 1))))
		return (-1);
	i = -1;
	while (++i < size)
		(*line)[i] = lst->stock[i];
	(*line)[i] = 0;
	tmp = NULL;
	if (*(lst->stock + size) == '\n')
		if (!(tmp = ft_strdup(lst->stock + size + 1)))
			return (-1);
	free(lst->stock);
	lst->stock = tmp;
	return (1);
}
