/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 13:23:51 by cseguier          #+#    #+#             */
/*   Updated: 2020/02/26 01:40:25 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/../includes/libft.h"

void	ft_lstadd(t_lftlist **start, t_lftlist *link)
{
	if (*start != NULL)
		link->next = *start;
	*start = link;
}
