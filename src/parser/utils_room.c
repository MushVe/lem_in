/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_room.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 06:40:54 by cseguier          #+#    #+#             */
/*   Updated: 2020/03/06 06:42:08 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

int		white_space_count(char *line)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (line[++i])
		count += line[i] == ' ';
	return (count);
}

int		is_room(char *line)
{
	int to_ret;
	int comment;
	int command;
	int spaces;

	comment = is_comment(line);
	command = is_command(line);
	spaces = white_space_count(line);
	to_ret = !comment && !command && line[0] != 'L' && spaces == 2
		&& ft_isalnum(line[0]);
	return (to_ret);
}

int		is_room_name_alphanumerical(char *line)
{
	int		i;
	int		ret;
	char	*stop;

	i = -1;
	ret = 0;
	stop = ft_strchr(line, ' ');
	while ((line[++i]) && (line + i != stop))
		ret += ft_isalnum(line[i]) || line[i] == '_';
	return (ret == i);
}

int		is_coord_only_digit(char *line)
{
	int		i;
	int		ret;
	char	*start;

	i = -1;
	ret = 0;
	start = ft_strchr(line, ' ');
	while (start[++i])
		ret += ft_isdigit(start[i]) || start[i] == ' ';
	return (ret == i);
}

int		is_coord_valid(char *line)
{
	int		i;
	int		ret;
	char	*start;

	i = 1;
	ret = 0;
	start = ft_strchr(line, ' ');
	if (!ft_isdigit(start[i]))
		return (0);
	ret += 1;
	i++;
	while (start[i] != ' ' && start[i])
		i++;
	if (!ft_isdigit(start[i + 1]))
		return (0);
	else
		ret += 1;
	return (ret == 2);
}

int		is_tube(char *line)
{
	return (ft_strchr(line, '-') != NULL);
}
