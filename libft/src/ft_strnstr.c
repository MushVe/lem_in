/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 18:41:00 by cseguier          #+#    #+#             */
/*   Updated: 2020/02/26 01:41:50 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(char const *str, char const *need, size_t len)
{
	size_t	i;
	size_t	buff;
	size_t	j;

	buff = 0;
	if (need[buff] == '\0')
		return ((char*)str);
	while (str[buff] != '\0')
	{
		j = 0;
		if (str[buff] == need[j])
		{
			i = buff;
			while (str[i] == need[j] && need[j] != '\0' && str[i] != '\0' \
					&& i < len)
			{
				i++;
				j++;
			}
			if (need[j] == '\0')
				return ((char*)&str[buff]);
		}
		buff++;
	}
	return (NULL);
}
