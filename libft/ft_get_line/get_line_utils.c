/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 01:35:18 by cseguier          #+#    #+#             */
/*   Updated: 2020/02/26 01:35:20 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_get_line.h"

bool is_storage_empty(char *storage)
{
	// printf("What does storage contain %s <%c>\n", storage == NULL ? "nothing" : storage, storage != NULL ? storage[0] : '\0');
	return (storage == NULL || *storage == '\0');
}

bool contain_new_line(char *data, char **new_line_pos)
{
	char *index;

	index = NULL;
	if (data)
		return ((*new_line_pos = ft_strchr(data, '\n')) != NULL);
	return (false);
}

bool is_nl_last_char(char *data, char *new_line_pos)
{
	int index;

	index = new_line_pos - data;
	return (data[index] == '\n' && data[index + 1] == '\0');
}


void strjoin_free_s1(char **s1, char *s2)
{
	int size_s1;
	int size_s2;
	char *new_str;

	// printf("buffer: <<%s>>\n\n\n\n", s2);
	// printf("storage: ((%s))\n\n\n\n\n", *s1);
	new_str = NULL;
	size_s1 = ft_strlen(*s1);
	size_s2 = ft_strlen(s2);
	// printf("Inside: %s after the strlen\n", __func__);
	if (!(new_str = ft_memalloc(size_s1 + size_s2 + 1)))
		exit(0);
	if (!ft_strcpy(new_str, *s1))
	{
		exit(0);
	}
	if (!ft_strcpy(new_str + size_s1, s2))
	{
		exit(0);
	}
	// printf("new_str ???%s???\n\n", new_str);
	// printf("2nd strcpy %s\n", new_str);
	// printf("Inside: %s after the allocations\n", __func__);
	free(*s1);
	*s1 = new_str;
}



bool save_data(char **storage, char *buffer)
{
	static int i = 0;

	// printf("%d times in %s\n", i, __func__);
	i++;
	if (*storage)
	{
		// printf("storage is not empty in %s\n", __func__);
		// return ((*storage = strjoin_free_s1(storage, buffer)) != NULL);
	}
	// printf("first allocation of storage in %s\n", __func__);
	return ((*storage = ft_strdup(buffer)) != NULL);
}