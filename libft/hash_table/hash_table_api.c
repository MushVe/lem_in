/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_api.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 01:35:26 by cseguier          #+#    #+#             */
/*   Updated: 2020/02/27 05:19:56 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/hash_table.h"

/*
** Create an empty hash table
** {Input} : Take a number of item as an arg, multiply it by 100 to lower collision
** And a control structure to track the capacity
** {Return} the newly allocated hash_table
** Or NULL if it couldn't allocate
*/

t_ht		*hash_table_create(size_t item_count, t_hthandle *t_hthandler)
{
	t_ht	*hash_table;
	int		i;

	i = -1;
	//	calculer taille par rapport au nombre d'items et pas mettre valeur fixe
	if (!(hash_table = ft_memalloc(item_count * 100 * sizeof(t_ht))))
		return (0);
	t_hthandler->capacity = item_count;
	t_hthandler->modulo = item_count * 10;
	t_hthandler->current_capacity = item_count;
	t_hthandler->hash_table = hash_table;
	while (++i < item_count * 100)
		hash_table[i].key = -1;
	return (hash_table);
}

void	free_content(char **content)
{
	free(*content);
	*content = NULL;
}

void	free_node(t_ht **node)
{
	free(*node);
	*node = NULL;
}

void	delete_list(t_ht **collision_list)
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

int		hash_table_delete(t_hthandle *t_hthandler)
{
	int		size;
	int		i;
	char	*to_free;
	t_ht		*collision_list;

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
** Put the data in the hash_table
** {Input} : Take a control structure to track the capacity
** And the data to add
** Return 0 if it could not put the data
** Return 1 if it could
*/

int		hash_table_put(t_hthandle *t_hthandler, char *data, int index)
{
	t_ht		*hash_table;
	size_t	key;
	int		ret;

	ret = 0;
	if (!t_hthandler->hash_table)
		return (0);
	if (t_hthandler->current_capacity < 1)
		return (0);
	key = ht_hash(data) % t_hthandler->modulo;
	hash_table = &t_hthandler->hash_table[key];
	if (hash_table->key == -1)
		ret = ht_fill_hash_table(hash_table, key, data, NULL, index);
	else if (ft_strcmp(data, hash_table->room_name) != 0)
		ret = ht_handle_collision(hash_table, data, key, index);
	if (ret)
		t_hthandler->current_capacity -= 1;
	return (ret);
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
	t_ht		*hash_table;
	t_ht		*store;
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
