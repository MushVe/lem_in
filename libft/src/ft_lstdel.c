/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 13:42:06 by cseguier          #+#    #+#             */
/*   Updated: 2020/02/26 01:40:26 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/../includes/libft.h"

void	ft_lstdel(t_lftlist **alst, void (*del)(void *, size_t))
{
	t_lftlist	*list;

	if (alst != NULL && del != NULL)
	{
		list = (*alst)->next;
		while (list)
		{
			list = (*alst)->next;
			del((*alst)->content, (*alst)->content_size);
			ft_memdel((void **)alst);
			(*alst) = list;
		}
	}
}
