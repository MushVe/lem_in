/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 01:31:58 by cseguier          #+#    #+#             */
/*   Updated: 2020/02/26 03:53:59 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_list			*create_node(char *data)
{
	t_list	*node;

	if (data == NULL)
		exit_error("Data to insert in list is NULL\n", (char*)__func__);
	if (!(node = malloc(sizeof(t_list))))
		exit_error("Malloc failed\n", (char*)__func__);
	node->data = data;
	node->next = NULL;
	return (node);
}

int				add_front_node(t_list **head, char *data)
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

map_room_index	*store_rooms(t_anthill data, h_t_handle *h_t_handler, t_list *rooms)
{
	int				i;
	map_room_index	*junction_table;
	char			*splitted;

	i = 0;
	if (!(junction_table = malloc(sizeof(map_room_index) * (data.room_count + 1))))
		exit_error("Malloc failed\n", (char*)__func__);
	while (rooms)
	{
		if (is_room(rooms->data) && is_room_valid(rooms->data))
		{
			splitted = allocate_room(rooms->data);
			hash_table_put(h_t_handler, splitted, i);
			junction_table[i].index = i;
			junction_table[i].room_name = splitted;
			i++;
		}
		rooms = rooms->next;
	}
	return (junction_table);
}

/*
** Possibles erreurs dans le parsing des rooms
** alors, est-ce qu'on considere que si la salle recue
** ne contient pas de coordonnées x,y c'est une erreur et on arrete le parsing ?
** est-ce que deux commandes a la suite est un motif d'arret du parsing
** est-ce que le start et end sont reassignable ?
** #######
** Steps:
** 1/ Get the ants_count return_ants()
** Verify Pitfalls
** if No error => Proceed
** 2/Get the rooms
** Verify Pitfalls
*/

void			init(t_anthill *data, t_list *tmp, h_t_handle *h_t_handler)
{
	data->ant_count = 0;
	data->room_count = 0;
	data->rooms.end = NULL;
	data->rooms.start = NULL;
	h_t_handler->capacity = 0;
	h_t_handler->current_capacity = 0;
	h_t_handler->hash_table = NULL;
	h_t_handler->modulo = 0;
}

void			delete_junction_table(map_room_index *junction)
{
	free(junction);
}

void			delete_display_list(t_list *list)
{
	t_list *next;

	next = NULL;
	while (list)
	{
		next = list->next;
		free(list);
		list = next;
	}
}

/*
** display
*/

void			display_anthill(t_list *list)
{
	if (list != NULL)
		display_anthill(list->next);
	if (list)
		ft_printf("%s\n", list->data);
}

void			display(t_anthill data, t_list *list)
{
	printf("%lld\n%s\n", data.ant_count, list->data);
	display_anthill(list->next);
}

/*
** Return the matrix storing the connections
** between the lines
*/

void			clean(h_t_handle *handle, t_list *list, map_room_index *junction, t_anthill data)
{
	delete_display_list(list);
	hash_table_delete(handle);
	delete_junction_table(junction);
	free(data.rooms.end);
	free(data.rooms.start);
}

int				**parser(int *size, char **line, char **storage)
{
	t_anthill		data;
	t_list			*tmp;
	h_t_handle		h_t_handler;
	map_room_index	*junction;
	int				**matrix;

	*line = NULL;
	tmp = NULL;
	init(&data, tmp, &h_t_handler);
	handle_ants(line, &data, storage);
	if (!handle_rooms(line, &tmp, &data, 0, storage))
		exit_error("ERROR, room parsing failed\n", (char*)__func__);
	hash_table_create(data.room_count, &h_t_handler);
	junction = store_rooms(data, &h_t_handler, tmp);
	if (!(matrix = handle_tubes(line, &tmp, &h_t_handler, data.room_count, storage)))
		exit_error("ERROR, tubes parsing failed\n", (char*)__func__);  // Pas sur, voir si on a assez de data pour faire le traiteme, (char*)__func__nt
	*size = data.room_count;
	/*
	** Attention a ne pas utiliser avant la fin du programme hein
	*/
	display(data, tmp);
	free(*storage);
	clean(&h_t_handler, tmp, junction, data);
	return (matrix);
}
