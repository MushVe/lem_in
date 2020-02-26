/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 13:29:54 by cseguier          #+#    #+#             */
/*   Updated: 2020/02/26 01:40:29 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/../includes/libft.h"

void	ft_lstiter(t_lftlist *lst, void (*f)(t_lftlist *elem))
{
	t_lftlist	*list;

	while (lst)
	{
		list = lst->next;
		f(lst);
		lst = list;
	}
}
