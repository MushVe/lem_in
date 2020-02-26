/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 01:35:42 by cseguier          #+#    #+#             */
/*   Updated: 2020/02/26 05:54:13 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_TABLE_H
# define HASH_TABLE_H

# include "libft.h"

typedef struct	s_h_t
{
	long long	key;
	char		*room_name;
	int			index;
	struct t_ht	*next;
}				t_ht;

typedef struct	s_hthandle
{
	t_ht	*hash_table;
	size_t	capacity;
	size_t	current_capacity;
	size_t	modulo;
}				t_hthandle;

/*
** Utils for the hash table
*/

int				ht_fill_hash_table(t_ht *element, size_t key, char *data, t_ht *next, int index);
int				ht_find_match_store(t_ht *hash_table, char *to_compare, t_ht **store);
int				ht_handle_collision(t_ht *hash_table, char *data, size_t key, int index);
size_t			ht_hash(char *cp);

/*
** Hash table API
*/

t_ht			*hash_table_create(size_t item_count, t_hthandle *t_hthandler);
int				hash_table_delete(t_hthandle *t_hthandler);
t_ht			*hash_table_get(t_hthandle *t_hthandler, char *to_get);
int				hash_table_put(t_hthandle *t_hthandler, char *data, int index);
// hash_table_delete(t_hthandle *t_hthandler)

#endif
