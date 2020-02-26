/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 16:59:32 by cseguier          #+#    #+#             */
/*   Updated: 2020/02/26 01:41:12 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strcdup(char const *src, char c)
{
	char	*s;

	if (!(s = (char*)ft_memalloc((sizeof(*s) * (ft_strlen(src) + 1)))))
		return (0);
	return (ft_strccpy(s, src, c));
}
