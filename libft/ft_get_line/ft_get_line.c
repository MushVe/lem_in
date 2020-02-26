/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 01:35:12 by cseguier          #+#    #+#             */
/*   Updated: 2020/02/26 01:35:15 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_get_line.h"

char *my_strtok(char *line, int *end)
{
	static int index = 0;
	int offset;

	if (index != 0)
		index++;
	offset = index;
	while (line[index])
	{
		if (line[index] == '\n')
		{
			line[index] = '\0';
			return (line + offset);
		}
		index++;
	}
	index = 0;
	*end = 0;
	return (line + offset);
}

static bool return_line(char *storage, char **line)
{
	static int end = 1;

	if (end == 0)
		return (0);
	*line = my_strtok(storage, &end);
	return (1);

}

static int store_lines(int fd, char **storage, char *buffer, f_list *func)
{
	int ret;

	ret = 0;
	
	while ((ret = read(fd, buffer, BUFFA_SIZE)) > 0)
	{
		func->my_strjoin(storage, buffer);
		func = func->next;
		ft_bzero(buffer, BUFFA_SIZE + 1);
	}
	return (ret);
}

void my_strdup(char **dest, char *src)
{
	if (!(*dest = ft_strdup(src)))
		exit(0);
}

void _init(f_list *func)
{
	func[0].my_strjoin = &my_strdup;
	func[0].next = &func[1];
	func[1].my_strjoin = &strjoin_free_s1;
	func[1].next = &func[1];
}

int ft_get_line(int fd, char **line, char **storage)
{
	f_list func[2];
	char buffer[BUFFA_SIZE + 1];

	ft_bzero(buffer, BUFFA_SIZE + 1);
	_init(func);
	if (is_storage_empty(*storage) == false)
		return (return_line(*storage, line));
	store_lines(fd, storage, buffer, func);
	return (return_line(*storage, line));
}
