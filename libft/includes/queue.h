/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 01:37:18 by cseguier          #+#    #+#             */
/*   Updated: 2020/02/27 05:06:51 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_H
# define QUEUE_H

# include "libft.h"

typedef struct	s_qnode
{
	char			*data;
	struct s_qnode	*next;
}				t_qnode;

/*
** The queue, front stores the front node of LL and rear stores the
** last node of LL
*/

typedef struct	s_queue
{
	t_qnode	*front;
	t_qnode	*rear;
}				t_queue;

void			en_queue(t_queue *q, char *data);
void			de_queue(t_queue *q);

#endif
