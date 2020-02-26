/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 12:16:32 by cseguier          #+#    #+#             */
/*   Updated: 2020/02/26 01:40:32 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_lftlist	*ft_lstnew(void const *content, size_t content_size)
{
	t_lftlist	*link;

	if (!(link = (t_lftlist *)ft_memalloc(sizeof(t_lftlist))))
		return (NULL);
	if (link == NULL)
		return (NULL);
	if (content == NULL)
	{
		link->content = NULL;
		link->content_size = 0;
	}
	else
	{
		if (!(link->content = ft_memalloc(content_size)))
			return (NULL);
		if (link->content == NULL)
			return (NULL);
		ft_memcpy((link->content), content, content_size);
		link->content_size = content_size;
	}
	link->next = NULL;
	return (link);
}
