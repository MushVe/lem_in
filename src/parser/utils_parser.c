/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 06:50:20 by cseguier          #+#    #+#             */
/*   Updated: 2020/03/06 06:54:34 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

t_list				*create_node(char *data)
{
	t_list	*node;

	if (data == NULL)
		exit_error("Data to insert in list is NULL\n", (char*)__func__);
	if (!(node = ft_memalloc(sizeof(t_list))))
		exit_error("Malloc failed\n", (char*)__func__);
	node->data = data;
	node->next = NULL;
	return (node);
}

int					add_front_node(t_list **head, char *data)
{
	t_list	*tmp;

	if (!*head)
	{
		if (!(*head = create_node(data)))
			exit_error("Malloc failed\n", (char*)__func__);
		return (1);
	}
	tmp = (*head)->next;
	if (!((*head)->next = create_node(data)))
		exit_error("Malloc failed\n", (char*)__func__);
	(*head)->next->next = tmp;
	return (1);
}

t_map_room_index	*store_rooms(t_anthill *data, t_hthandle *ht, t_list *rooms)
{
	int					i;
	t_map_room_index	*junction_table;
	char				*splitted;

	i = 0;
	if (!(junction_table = ft_memalloc(sizeof(t_map_room_index)
		* (data->room_count + 1))))
		exit_error("Malloc failed\n", (char*)__func__);
	while (rooms)
	{
		if (is_room(rooms->data) && is_room_valid(rooms->data))
		{
			splitted = allocate_room(rooms->data);
			hash_table_put(ht, splitted, i);
			junction_table[i].index = i;
			junction_table[i].room_name = splitted;
			i++;
		}
		rooms = rooms->next;
	}
	data->rooms.start_index = hash_table_get(ht, data->rooms.start)->index;
	data->rooms.end_index = hash_table_get(ht, data->rooms.end)->index;
	return (junction_table);
}
