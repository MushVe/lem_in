/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 14:29:40 by snedir            #+#    #+#             */
/*   Updated: 2020/02/08 02:37:56 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static t_gnl	*new(int fd)
{
	t_gnl	*control;

	if (!(control = (t_gnl*)ft_memalloc(sizeof(t_gnl))))
		return (0);
	control->next = NULL;
	control->prev = NULL;
	control->stock = NULL;
	control->fd = fd;
	return (control);
}

static t_gnl	*add_node(t_gnl *elem, int fd)
{
	t_gnl	*control;

	while (elem)
	{
		if (elem->fd == fd)
			return (elem);
		if (elem->next == NULL)
		{
			while (elem)
			{
				if (elem->fd == fd)
					return (elem);
				if (elem->prev == NULL)
					break ;
				elem = elem->prev;
			}
			break ;
		}
		elem = elem->next;
	}
	control = new(fd);
	control->next = elem;
	elem->prev = control;
	return (control);
}

static int		god_like(char *buf, t_gnl *control, char **line, int way)
{
	char	*tmp;
	char	*tmp2;

	if ((tmp = ft_strchr(buf, '\n')) && (way == 1))
	{
		*tmp = '\0';
		*line = ft_gnl_strjoin2(control->stock, buf);
		ft_memdel((void*)&control->stock);
		control->stock = ft_strdup(tmp + 1);
		return (1);
	}
	else if ((tmp = ft_strchr(control->stock, '\n')) && (way == 2))
	{
		tmp2 = ft_strdup(tmp + 1);
		*tmp = '\0';
		*line = ft_strdup(control->stock);
		ft_memdel((void*)&control->stock);
		control->stock = ft_strdup(tmp2);
		ft_memdel((void*)&tmp2);
		return (1);
	}
	return (0);
}

static int		read_mem(int fd, char *buf, t_gnl *control, char **line)
{
	int	ret;

	ret = 0;
	if (fd < 0)
		return (-1);
	while ((ret = read(fd, buf, GNL_BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (god_like(buf, control, line, 1))
			return (1);
		control->stock = ft_gnl_strjoinf(control->stock, buf);
	}
	if (ret == -1)
		return (-1);
	if (control->stock)
	{
		if (*control->stock == '\0')
			return (0);
		*line = ft_strdup(control->stock);
		control->stock = NULL;
		return (1);
	}
	return (0);
}

int				get_next_line(int const fd, char **line)
{
	static t_gnl	*control = NULL;
	char			buf[GNL_BUFF_SIZE + 1];
	int				ret;

	if (!line)
		return (-1);
	if (control && fd != control->fd)
		control = add_node(control, fd);
	if (!control)
		control = new(fd);
	if (control->stock)
		if (god_like(buf, control, line, 2))
			return (1);
	ret = read_mem(fd, buf, control, line);
	if (ret == 1)
		return (1);
	else if (ret == -1)
		return (-1);
	else
		return (0);
}
