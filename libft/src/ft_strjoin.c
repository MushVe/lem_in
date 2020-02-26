/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:12:48 by cseguier          #+#    #+#             */
/*   Updated: 2020/02/26 01:41:34 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static void	now_free(char *s1, char *s2, int id)
{
	if (id == 1 || id == 3)
		ft_memdel((void*)&s1);
	if (id == 2 || id == 3)
		ft_memdel((void*)&s2);
}

char		*ft_strjoin(char *s1, char *s2, int id)
{
	int		i;
	char	*page;
	int		t1;
	int		t2;

	i = -1;
	if (!s1 || !s2)
		return (NULL);
	t1 = ft_strlen(s1);
	t2 = ft_strlen(s2);
	if (!(page = (char*)ft_memalloc(sizeof(char) * (t1 + t2 + 1))))
		return (0);
	while (++i < t1)
		page[i] = s1[i];
	i--;
	while (++i < t1 + t2)
		page[i] = s2[i - t1];
	page[i] = '\0';
	if (id != 0)
		now_free(s1, s2, id);
	return (page);
}
