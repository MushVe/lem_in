/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 12:16:10 by cseguier          #+#    #+#             */
/*   Updated: 2020/02/26 01:41:54 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strrev(char const *str, size_t len)
{
	size_t	i;
	char	*res;
	char	buff;

	if (!str)
		return (NULL);
	i = 0;
	buff = '0';
	if (!(res = ft_strdup(str)))
		return (NULL);
	while (len > i)
	{
		buff = res[len];
		res[len] = res[i];
		res[i] = buff;
		i++;
		len--;
	}
	return (res);
}
