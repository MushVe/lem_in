/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 01:35:31 by cseguier          #+#    #+#             */
/*   Updated: 2020/03/06 06:03:03 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/hash_table.h"

/*
** Assign value to a hash_table
** {Input} : The hash table
** The key (hash of the elem)
** The data to add
** And a value for the next collision pointer if needed
** {Return} : Return a value to conveniently use in a return :)
*/

int			ht_fill_hash_table(t_ht *e, size_t key, char *data, int index)
{
	e->key = key;
	e->index = index;
	e->room_name = data;
	e->next = NULL;
	return (1);
}

/*
** Handle the case where we try to add an already existing elem
** {Input} : The hash table
** The Data we will compare
** The tmp storage we use to store the last elem of the collision list
** If it isn't a false positive
** {Return} : a boolean value for success or failure
*/

static int	is_false_positive(t_ht *hash_table, char *data, t_ht **tmp)
{
	return (ht_find_match_store(hash_table, data, tmp));
}

/*
** Handle the collision
** 2 cases :
** 1/ Element we try to add already exist
** 2/ Real collision so we add a new node to the linked list
** {Input} : the hash table
** The Data we will compare
** The key of the item we might create
** {Return} : a boolean value for success or failure
*/

int			ht_handle_collision(t_ht *ht, char *data, size_t key, int index)
{
	t_ht		*tmp;

	tmp = NULL;
	if (is_false_positive(ht, data, &tmp))
		return (1);
	if (tmp == NULL)
		tmp = ht;
	if (!(tmp->next = ft_memalloc(sizeof(t_ht))))
		return (0);
	return (ht_fill_hash_table(tmp->next, key, data, index));
}
