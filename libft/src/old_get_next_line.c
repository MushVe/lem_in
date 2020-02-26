/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_get_next_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 16:38:31 by cseguier          #+#    #+#             */
/*   Updated: 2020/02/26 01:43:06 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static char		*strc_dup_cpy(char const *src, char c)
{
	int		i;
	char	*dest;

	i = 0;
	if (!(dest = (char*)ft_memalloc((sizeof(char) * (ft_strlen(src) + 1)))))
		return (0);
	while (src[i] != c)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/*
** tmp = "\0"; ??????
*/

static int		copyinline(char **line, char **s)
{
	char	*tmp;

	tmp = "\0";
	if (ft_strchr(*s, '\n'))
	{
		if (!(*line = strc_dup_cpy(*s, '\n')))
			return (0);
		if (!(tmp = ft_strdup(1 + ft_strchr(*s, '\n'))))
			return (0);
	}
	else
	{
		if (!(*line = ft_strdup(*s)))
			return (0);
	}
	free(*s);
	*s = tmp;
	return (1);
}

static ssize_t	readfile(char **s, char **line, int fd, char *buff)
{
	ssize_t	lu;

	ft_memset(buff, 0, GNL_BUFF_SIZE + 1);
	lu = 1;
	while (0 < (lu = read(fd, buff, GNL_BUFF_SIZE)))
	{
		if (!(*s = ft_strjoin(*s, buff, 0)))
			return (-1);
		ft_memset(buff, 0, GNL_BUFF_SIZE + 1);
	}
	if (lu == -1)
		return (-1);
	if (**s)
	{
		if (!copyinline(line, s))
			return (-1);
		return (1);
	}
	return (0);
}

int				me_get_next_line(int const fd, char **line)
{
	static char	*s;
	char		buff[GNL_BUFF_SIZE + 1];
	ssize_t		lu;

	if (fd < 0 || !line)
		return (-1);
	if (s == NULL)
		s = "\0";
	lu = readfile(&s, line, fd, buff);
	if (lu > 0)
		return (1);
	if (lu < 0)
		return (-1);
	return (0);
}
