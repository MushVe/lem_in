/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 01:35:18 by cseguier          #+#    #+#             */
/*   Updated: 2020/03/06 05:36:48 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

bool	gl_is_storage_empty(char *storage)
{
	return (storage == NULL || *storage == '\0');
}

bool	gl_contain_new_line(char *data, char **new_line_pos)
{
	char	*index;

	index = NULL;
	if (data)
		return ((*new_line_pos = ft_strchr(data, '\n')) != NULL);
	return (false);
}

bool	gl_is_nl_last_char(char *data, char *new_line_pos)
{
	int	index;

	index = new_line_pos - data;
	return (data[index] == '\n' && data[index + 1] == '\0');
}

void	gl_strjoin_free_s1(char **s1, char *s2)
{
	int		size_s1;
	int		size_s2;
	char	*new_str;

	new_str = NULL;
	size_s1 = ft_strlen(*s1);
	size_s2 = ft_strlen(s2);
	if (!(new_str = ft_memalloc(size_s1 + size_s2 + 1)))
		exit(0);
	if (!ft_strcpy(new_str, *s1))
		exit(0);
	if (!ft_strcpy(new_str + size_s1, s2))
		exit(0);
	free(*s1);
	*s1 = new_str;
}

bool	gl_save_data(char **storage, char *buffer)
{
	return ((*storage = ft_strdup(buffer)) != NULL);
}
