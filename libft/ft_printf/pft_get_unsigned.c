/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pft_get_unsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:01:55 by cseguier          #+#    #+#             */
/*   Updated: 2019/11/13 01:50:04 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

unsigned int	pft_get_size(t_pf *p, unsigned int nbr)
{
	if (p->op_type == 11)
		nbr = (unsigned short)nbr;
	if (p->op_type == 12)
		nbr = (unsigned char)nbr;
	return (nbr);
}

char			*pft_get_uint(char c, va_list ap, t_pf *p)
{
	unsigned int	nbr;
	char			*res;

	nbr = va_arg(ap, unsigned int);
	nbr = pft_get_size(p, nbr);
	if (c == 'x' || c == 'p')
	{
		if (!(res = ft_itoa_base(nbr, 16, 1)))
			return (0);
	}
	else if (c == 'X')
	{
		if (!(res = ft_itoa_base(nbr, 16, 0)))
			return (0);
	}
	else if (c == 'o')
	{
		if (!(res = ft_itoa_base(nbr, 8, 1)))
			return (0);
	}
	else if (!(res = pft_convert_unsigned((unsigned long long)nbr)))
		return (0);
	return (res);
}

char			*pft_get_ulong(char c, va_list ap)
{
	unsigned long	nbr;
	char			*res;

	nbr = va_arg(ap, unsigned long);
	if (c == 'x' || c == 'p')
	{
		if (!(res = ft_itoa_base(nbr, 16, 1)))
			return (0);
	}
	else if (c == 'X')
	{
		if (!(res = ft_itoa_base(nbr, 16, 0)))
			return (0);
	}
	else if (c == 'o')
	{
		if (!(res = ft_itoa_base(nbr, 8, 1)))
			return (0);
	}
	else if (!(res = pft_convert_unsigned((unsigned long long)nbr)))
		return (0);
	return (res);
}

char			*pft_get_ulonglong(char c, va_list ap)
{
	unsigned long long	nbr;
	char				*res;

	nbr = va_arg(ap, unsigned long long);
	if (c == 'x' || c == 'p')
	{
		if (!(res = ft_itoa_base(nbr, 16, 1)))
			return (0);
	}
	else if (c == 'X')
	{
		if (!(res = ft_itoa_base(nbr, 16, 0)))
			return (0);
	}
	else if (c == 'o')
	{
		if (!(res = ft_itoa_base(nbr, 8, 1)))
			return (0);
	}
	else if (!(res = pft_convert_unsigned((unsigned long long)nbr)))
		return (0);
	return (res);
}
