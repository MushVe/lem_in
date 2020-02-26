/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 15:08:38 by cseguier          #+#    #+#             */
/*   Updated: 2020/02/26 01:40:21 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/../includes/libft.h"

static void	nbr(int n, int i, char *s)
{
	int	max;

	max = 0;
	if (n < 0)
	{
		if (n == -2147483648)
		{
			max = 1;
			n++;
		}
		s[0] = '-';
		n = -n;
	}
	if (n >= 10)
		nbr(n / 10, i - 1, s);
	s[i] = (max == 1 ? ((n % 10) + '1') : ((n % 10) + '0'));
}

char		*ft_itoa(int n)
{
	char	*str;
	int		cpt;
	int		nb;

	cpt = 0;
	nb = n;
	while (nb != 0)
	{
		cpt++;
		nb = nb / 10;
	}
	if (n <= 0)
		cpt++;
	if (!(str = ft_strnew(cpt)))
		return (NULL);
	nbr(n, cpt - 1, str);
	return (str);
}
