/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pft_get_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:01:55 by cseguier          #+#    #+#             */
/*   Updated: 2019/11/13 01:41:29 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*pft_get_string(char c, va_list ap)
{
	char	*res;
	char	*tmp;

	(void)c;
	tmp = va_arg(ap, char*);
	if (tmp == NULL)
		res = ft_strdup("(null)");
	else
		res = ft_strdup(tmp);
	return (res);
}

char	*pft_get_char(char c, va_list ap, t_pf *p)
{
	char	*res;

	(void)c;
	if (!(res = ft_strnew(1)))
		return (0);
	res[0] = va_arg(ap, int);
	return (res);
}

char	*pft_get_longdouble(char c, va_list ap)
{
	long double	res;

	(void)c;
	res = va_arg(ap, long double);
	return (0);
}

char	*pft_get_double(char c, va_list ap)
{
	double	res;

	(void)c;
	res = va_arg(ap, double);
	return (0);
}
