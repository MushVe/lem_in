/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 05:52:25 by cseguier          #+#    #+#             */
/*   Updated: 2020/03/06 06:07:47 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/hash_table.h"

/*
** Create an empty hash table
** {Input} : Take a number of item as an arg,
** multiply it by 100 to lower collision
** And a control structure to track the capacity
** {Return} the newly allocated hash_table
** Or NULL if it couldn't allocate
** ps: calculer taille par rapport au nombre d'items
** et pas mettre valeur fixe
*/

t_ht	*hash_table_create(size_t item_count, t_hthandle *t_hthandler)
{
	t_ht	*hash_table;
	size_t	i;

	i = 0;
	if (!(hash_table = ft_memalloc(item_count * 100 * sizeof(t_ht))))
		return (0);
	t_hthandler->capacity = item_count;
	t_hthandler->modulo = item_count * 10;
	t_hthandler->current_capacity = item_count;
	t_hthandler->hash_table = hash_table;
	while (i < item_count * 100)
	{
		hash_table[i].key = -1;
		i++;
	}
	return (hash_table);
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
	t_ht	*hash_table;
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
		ret = ht_fill_hash_table(hash_table, key, data, index);
	else if (ft_strcmp(data, hash_table->room_name) != 0)
		ret = ht_handle_collision(hash_table, data, key, index);
	if (ret)
		t_hthandler->current_capacity -= 1;
	return (ret);
}

/*
** Basic non crytographic hash function
** {Input} : the string to hash
** {Return} : the hash
*/

size_t	ht_hash(char *cp)
{
	unsigned long	hash;
	int				c;

	hash = 5381;
	while ((c = *cp++))
		hash = ((hash << 5) + hash) + c;
	return (hash);
}

/*
** Iterate through the collision list and try to find a match
** {Input} : The linked list
** The string to find
** A pointer on a list pointer to store the match
** {Return} : a boolean value for success or failure
** And store the match, or the last element of the collision list
*/

int		ht_find_match_store(t_ht *ht, char *to_compare, t_ht **store)
{
	t_ht	*tmp;

	tmp = ht;
	while (tmp->next != NULL)
	{
		if (ft_strcmp(tmp->room_name, to_compare) == 0)
		{
			*store = tmp;
			return (1);
		}
		tmp = tmp->next;
	}
	if (ft_strcmp(tmp->room_name, to_compare) == 0)
	{
		*store = tmp;
		return (1);
	}
	*store = tmp;
	return (0);
}
