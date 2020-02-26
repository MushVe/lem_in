/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pft_flag_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:01:55 by cseguier          #+#    #+#             */
/*   Updated: 2019/11/13 01:48:16 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char	*set_zero(char *res)
{
	ft_memdel((void*)&res);
	if (!(res = ft_strdup("\0")))
		return (0);
	return (res);
}

static char	*next_process(char c, t_pf *p, char *res)
{
	if (pft_isflag(p->flag, p))
	{
		if (p->op_preci != 0 && p->flag != 'c')
			res = pft_add_preci(res, p, c);
		if (p->op_preci == 0 && p->op_point != 0
			&& (p->flag == 's' || p->flag == 'u'))
			if (!(res = set_zero(res)))
				return (0);
		if ((p->op_plus == 1 || p->op_space == 1)
			&& p->flag != 'c' && c != '%')
			res = pft_add_sign(res, p);
		if ((p->op_diese == 1 && p->flag != 'c') || p->flag == 'p')
			res = pft_add_x(res, c, p);
		if ((p->op_width != 0))
			res = pft_add_width(res, p);
	}
	else if (!(res = set_zero(res)))
		return (0);
	return (res);
}

static char	*first_process(char c, va_list ap, t_pf *p, char *res)
{
	if (c == 'd' || c == 'i')
	{
		if (p->op_type == 21 || p->op_type == 22)
			res = pft_get_longlong(ap);
		else
			res = pft_get_int(ap, p);
		if (!(ft_strcmp(res, "0")) && p->op_point == 1)
			if (!(res = set_zero(res)))
				return (0);
	}
	if (c == 'u' || c == 'o' || c == 'x' || c == 'X' || c == 'p')
	{
		if (p->op_type == 21 || p->op_type == 22 || c == 'p')
			res = pft_get_ulonglong(c, ap);
		else
			res = pft_get_uint(c, ap, p);
		if (!(ft_strcmp(res, "0")) && (p->op_diese == 0 && p->op_point == 1)
			&& (c == 'x' || c == 'X' || c == 'o' || c == 'p'))
			if (!(res = set_zero(res)))
				return (0);
	}
	return (res);
}

int		ptf_process(char c, va_list ap, t_pf *p)
{
	char	*res;

	res = NULL;
	if (c == '%')
	{
		if (!(res = ft_strdup("%")))
			return (0);
	}
	res = first_process(c, ap, p, res);
	if (c == 'c')
		res = pft_get_char(c, ap, p);
	if (c == 's')
		res = pft_get_string(c, ap);
	res = next_process(c, p, res);
	if (!(ptf_new_node(res, ft_strlen(res), p)))
		return (0);
	return (0);
}
