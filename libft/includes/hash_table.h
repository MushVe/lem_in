/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 01:35:42 by cseguier          #+#    #+#             */
/*   Updated: 2020/02/26 01:35:43 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "libft.h"

typedef struct 			h_t 
{
	long long			key;
	char				*room_name;
	int					index;
	struct h_t 			*next;
}						h_t;

typedef struct 			h_t_handle
{
	h_t					*hash_table;
	size_t				capacity;
	size_t				current_capacity;
	size_t				modulo;
}						h_t_handle;

/*
** Utils for the hash table
*/

int		ht_fill_hash_table(h_t *element, size_t key, char *data, h_t *next, int index);
int		ht_find_match_store(h_t *hash_table, char *to_compare, h_t **store);
int		ht_handle_collision(h_t *hash_table, char *data, size_t key, int index);
size_t	ht_hash(char *cp);


/*
** Hash table API
*/

h_t		*hash_table_create(size_t item_count, h_t_handle *h_t_handler);
int		hash_table_delete(h_t_handle *h_t_handler);
h_t		*hash_table_get(h_t_handle *h_t_handler, char *to_get);
int		hash_table_put(h_t_handle *h_t_handler, char *data, int index);
// hash_table_delete(h_t_handle *h_t_handler)

#endif