/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 17:32:22 by cseguier          #+#    #+#             */
/*   Updated: 2020/02/26 01:41:09 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strcat(char *dest, char const *src)
{
	int	cpt;
	int	i;

	i = 0;
	cpt = 0;
	while (dest[cpt] != '\0')
		cpt++;
	while (src[i] != '\0')
	{
		dest[cpt] = src[i];
		i++;
		cpt++;
	}
	dest[cpt] = '\0';
	return (dest);
}
