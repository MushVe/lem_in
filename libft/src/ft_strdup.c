/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 13:33:36 by cseguier          #+#    #+#             */
/*   Updated: 2020/02/26 01:41:23 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdup(char const *src)
{
	char *s;

	if (!(s = (char*)ft_memalloc((sizeof(*s) * (ft_strlen(src) + 1)))))
		return (0);
	return (ft_strcpy(s, src));
}

char	*ft_strndup(char const *src, int n)
{
	char *s;

	if (!(s = (char*)ft_memalloc((sizeof(*s) * (n + 1)))))
		return (0);
	return (ft_strncpy(s, src, n));
}