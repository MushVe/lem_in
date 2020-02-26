/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pft_get_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:01:55 by cseguier          #+#    #+#             */
/*   Updated: 2019/11/13 01:49:41 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*pft_get_int(va_list ap, t_pf *p)
{
	int		nbr;
	char	*res;

	nbr = va_arg(ap, int);
	if (p->op_type == 11)
	{
		if (!(res = pft_convert_signed((short)nbr)))
			return (0);
	}
	else if (p->op_type == 12)
	{
		if (!(res = pft_convert_signed((char)nbr)))
			return (0);
	}
	else
	{
		if (!(res = pft_convert_signed((long long)nbr)))
			return (0);
	}
	return (res);
}

char	*pft_get_long(va_list ap)
{
	long	nbr;
	char	*res;

	nbr = va_arg(ap, long);
	if (!(res = pft_convert_signed((long long)nbr)))
		return (0);
	return (res);
}

char	*pft_get_longlong(va_list ap)
{
	long long	nbr;
	char		*res;

	nbr = va_arg(ap, long long);
	if (!(res = pft_convert_signed((long long)nbr)))
		return (0);
	return (res);
}
