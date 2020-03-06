/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_api.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 01:35:26 by cseguier          #+#    #+#             */
/*   Updated: 2020/03/06 06:08:09 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/hash_table.h"

static void	free_content(char **content)
{
	free(*content);
	*content = NULL;
}

static void	free_node(t_ht **node)
{
	free(*node);
	*node = NULL;
}

static void	delete_list(t_ht **collision_list)
{
	t_ht	*node;
	t_ht	*node_to_free;
	char	*to_free;

	node = *collision_list;
	node_to_free = NULL;
	to_free = NULL;
	while (node)
	{
		to_free = node->room_name;
		node_to_free = node;
		node = node->next;
		if (to_free)
			free_content(&to_free);
		if (node_to_free)
			free_node(&node_to_free);
	}
	*collision_list = NULL;
}

int			hash_table_delete(t_hthandle *t_hthandler)
{
	int		size;
	int		i;
	char	*to_free;
	t_ht	*collision_list;

	i = -1;
	size = t_hthandler->capacity * 100;
	collision_list = NULL;
	while (++i < size)
	{
		to_free = t_hthandler->hash_table[i].room_name;
		collision_list = t_hthandler->hash_table[i].next;
		if (to_free)
			free_content(&to_free);
		if (collision_list)
			delete_list(&collision_list);
	}
	free(t_hthandler->hash_table);
	return (1);
}

/*
** Get the data from the hashtable
** {Input} : Take the control structure, the key of the item
** And the string to get in case of collision
** {Return} : the string if everything went well
** And NULL if shit goes wrong
*/

t_ht		*hash_table_get(t_hthandle *t_hthandler, char *to_get)
{
	t_ht	*hash_table;
	t_ht	*store;
	size_t	key;

	store = NULL;
	key = ht_hash(to_get) % t_hthandler->modulo;
	hash_table = &t_hthandler->hash_table[key];
	if (hash_table->key == -1)
		return (NULL);
	if (ht_find_match_store(hash_table, to_get, &store))
		return (store);
	return (NULL);
}
