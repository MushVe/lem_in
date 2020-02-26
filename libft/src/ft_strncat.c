/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 17:36:26 by cseguier          #+#    #+#             */
/*   Updated: 2020/02/26 01:41:42 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strncat(char *dest, char const *src, size_t n)
{
	size_t	cpt;
	size_t	i;

	i = 0;
	cpt = 0;
	while (dest[cpt] != '\0')
		cpt++;
	while (src[i] != '\0' && n > i)
	{
		dest[cpt] = src[i];
		i++;
		cpt++;
	}
	dest[cpt] = '\0';
	return (dest);
}
