/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 16:38:05 by cseguier          #+#    #+#             */
/*   Updated: 2020/02/26 01:41:40 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		t;
	int		i;
	char	*res;

	i = 0;
	if (!s)
		return (NULL);
	t = ft_strlen((char*)s);
	if (!(res = (char*)ft_memalloc(sizeof(char) * (t + 1))))
		return (0);
	while (s[i] != '\0')
	{
		res[i] = f(i, s[i]);
		i++;
	}
	return (res);
}
