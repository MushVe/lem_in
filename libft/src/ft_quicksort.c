/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quicksort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 16:39:05 by cseguier          #+#    #+#             */
/*   Updated: 2020/02/26 01:41:07 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static void	swap(char *a, char *b)
{
	char c;

	c = *b;
	*b = *a;
	*a = c;
}

static void	sort(char *s, size_t len)
{
	size_t	low;
	size_t	i;
	char	pivot;

	if (len < 2)
		return ;
	pivot = s[len - 1];
	low = 0;
	i = 0;
	while (i < len)
	{
		if (s[i] <= pivot)
		{
			if (low != i)
				swap(&s[i], &s[low]);
			low++;
		}
		i++;
	}
	sort(s, low - 1);
	sort(s + low - 1, len - low + 1);
}

char		*ft_quicksort(char const *s, size_t len)
{
	char	*res;

	if (!s || !len)
		return (NULL);
	if (len == 1)
		return ((char*)s);
	if (!(res = ft_strdup(s)))
		return (NULL);
	sort(res, len);
	return (res);
}
