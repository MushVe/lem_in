/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 01:32:08 by cseguier          #+#    #+#             */
/*   Updated: 2020/02/26 03:43:10 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

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
	spaces = white_space_count(line) == 2;
	to_ret = !comment && !command && line[0] != 'L' && spaces == 2;
	return (to_ret);
}

int		is_room_name_alphanumerical(char *line)
{
	int		i;
	int		ret;
	char	*stop;

	i = -1; // -1 si on est sur l'espace
	ret = 0;
	stop = ft_strchr(line, ' ');
	while ((line[++i]) && (line + i != stop))
		ret += ft_isascii(line[i]);
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

int		is_tube(char *line)
{
	return (ft_strchr(line, '-') != NULL);
}

int		is_room_valid(char *line)
{
	if (is_tube(line))
		return (0);
	if (!is_room_name_alphanumerical(line))
		return (0);
	if (!is_coord_only_digit(line))
		return (0);
	return (1);
}

int		got_start_end(int command_flag, t_anthill *data)
{
	int	not_empty;

	not_empty = (data->rooms.start != NULL && data->rooms.end != NULL);
	return (command_flag == 2 && not_empty);
}

void	assign_command(t_anthill *data, char *command, char *line)
{
	char	*tmp;
	int		diff;

	tmp = strchr(line, ' ');
	diff = tmp - line;
	if (command[0] == 's')
		if (!(data->rooms.start = strndup(line, diff)))
			exit_error("Malloc failed\n", (char*)__func__);
	if (command[0] == 'e')
		if (!(data->rooms.end = strndup(line, diff)))
			exit_error("Malloc failed\n", (char*)__func__);
}

char	*allocate_room(char *line)
{
	char	*stop;
	char	*to_ret;

	stop = ft_strchr(line, ' ');
	if (!(to_ret = strndup(line, stop - line)))
		return (NULL);
	return (to_ret);
}

int		handle_rooms(char **line, t_list **rooms, t_anthill *anthill, int command_flag, char **storage)
{
	char	*command;

	command = NULL;
	while (ft_get_line(0, line, storage) > 0)
	{
		if (!(add_front_node(rooms, *line)))
			return (0);
		if (is_empty(*line))
			return (0);
		else if (is_comment(*line))
			continue;
		else if (is_command(*line))
			command_flag += is_command_valid(*line, &command);
		else if (is_room(*line) && is_room_valid(*line))
		{
			if (command)
				assign_command(anthill, command, *line);
			anthill->room_count++;
			command = NULL;
		}
		else
			return (is_tube(*line) && got_start_end(command_flag, anthill));
	}
	return (0);
}
