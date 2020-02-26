/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pft_convert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:01:55 by cseguier          #+#    #+#             */
/*   Updated: 2019/11/13 01:42:49 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	nbr_signed(long long n, long long i, char *s)
{
	long long	max;
	long long	min;

	min = -9223372036854775807 - 1;
	max = 0;
	if (n < 0)
	{
		if (n == min)
		{
			max = 1;
			n++;
		}
		s[0] = '-';
		n = -n;
	}
	if (n >= 10)
		nbr_signed(n / 10, i - 1, s);
	s[i] = (max == 1 ? ((n % 10) + '1') : ((n % 10) + '0'));
}

char		*pft_convert_signed(long long n)
{
	char		*str;
	long long	cpt;
	long long	nb;

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
	nbr_signed(n, cpt - 1, str);
	return (str);
}

static void	nbr_unsigned(unsigned long long n, int i, char *s)
{
	if (n >= 10)
		nbr_unsigned(n / 10, i - 1, s);
	s[i] = (((n % 10) + '0'));
}

char		*pft_convert_unsigned(unsigned long long n)
{
	char				*str;
	unsigned long long	cpt;
	unsigned long long	nb;

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
	nbr_unsigned(n, cpt - 1, str);
	return (str);
}
