/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 01:35:31 by cseguier          #+#    #+#             */
/*   Updated: 2020/02/27 05:10:54 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/hash_table.h"

/*
** Basic non crytographic hash function
** {Input} : the string to hash
** {Return} : the hash
*/

size_t		ht_hash(char *cp)
{
	unsigned long	hash;
	int				c;

	hash = 5381;
	while ((c = *cp++))
		hash = ((hash << 5) + hash) + c;
	return (hash);
}

/*
** Assign value to a hash_table
** {Input} : The hash table
** The key (hash of the elem)
** The data to add
** And a value for the next collision pointer if needed
** {Return} : Return a value to conveniently use in a return :)
*/

int			ht_fill_hash_table(t_ht *element, size_t key, char *data, t_ht *next, int index)
{
	element->key = key;
	element->index = index;
	element->room_name = data;
	element->next = next;
	return (1);
}

/*
** Iterate through the collision list and try to find a match
** {Input} : The linked list
** The string to find
** A pointer on a list pointer to store the match
** {Return} : a boolean value for success or failure
** And store the match, or the last element of the collision list
*/

int			ht_find_match_store(t_ht *hash_table, char *to_compare, t_ht **store)
{
	t_ht	*tmp;

	tmp = hash_table;
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

int			ht_handle_collision(t_ht *hash_table, char *data, size_t key, int index)
{
	t_ht		*tmp;

	tmp = NULL;
	if (is_false_positive(hash_table, data, &tmp))
		return (1);
	if (tmp == NULL)
		tmp = hash_table;
	if (!(tmp->next = ft_memalloc(sizeof(t_ht))))
		return (0);
	return (ht_fill_hash_table(tmp->next, key, data, NULL, index));
}
