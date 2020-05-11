/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 01:32:08 by cseguier          #+#    #+#             */
/*   Updated: 2020/03/06 06:44:24 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

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

int		handle_rooms(char **line, t_list **rooms, t_anthill *ant)
{
	char	*command;
	int		command_flag;

	command_flag = 0;
	command = NULL;
	while (get_next_line(0, line) > 0)
	{
		if (!(add_front_node(rooms, *line)) || is_empty(*line))
			return (0);
		else if (is_comment(*line))
			continue;
		else if (is_command(*line))
			command_flag += is_command_valid(*line, &command);
		else if (is_room(*line) && is_room_valid(*line) && is_coord_valid(*line))
		{
			if (command)
				assign_command(ant, command, *line);
			ant->room_count++;
			command = NULL;
		}
		else
			return (is_tube(*line) && got_start_end(command_flag, ant));
	}
	return (0);
}
