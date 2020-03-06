/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pft_add_width.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:01:55 by cseguier          #+#    #+#             */
/*   Updated: 2020/03/06 05:46:00 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char	*pft_adjust_sign(char *res, char *it, t_pf *p)
{
	if ((p->op_diese == 1 && p->flag != 'c') || p->flag == 'p')
	{
		it = ft_strchr(res, 'x');
		it[0] = '0';
		if (p->flag == 'X')
			res[1] = 'X';
		if (p->flag == 'x' || p->flag == 'p')
			res[1] = 'x';
	}
	if (p->op_plus == 1 && p->flag != 'c' && p->flag != 'u'
			&& !(ft_strchr(res, '-')))
	{
		it = ft_strchr(res, '+');
		it[0] = '0';
		res[0] = '+';
	}
	return (res);
}

static char	*pft_adjust_width(char *res, char *it, int i, t_pf *p)
{
	while (++i < p->op_width)
		res = ft_strjoin("0", res, 2);
	if ((it = ft_strchr(res, '-')))
	{
		it[0] = '0';
		res[0] = '-';
	}
	res = pft_adjust_sign(res, it, p);
	if (p->op_space == 1 && p->flag != 'c' && p->flag != 'u'
			&& !(ft_strchr(res, '-')))
	{
		it = ft_strchr(res, ' ');
		it[0] = '0';
		res[0] = ' ';
	}
	return (res);
}

char		*pft_add_width(char *res, t_pf *p)
{
	int		i;
	char	*it;

	it = NULL;
	i = -1 + ft_strlen(res);
	if (p->null == 1)
		i++;
	if (p->op_less == 1)
		while (++i < p->op_width)
			res = ft_strjoin(res, " ", 1);
	else if ((p->op_zero == 1 && p->op_preci == 0)
		&& !(p->flag == 'p' && p->op_point == 1 && p->op_preci == 0))
		res = pft_adjust_width(res, it, i, p);
	else
		while (++i < p->op_width)
			res = ft_strjoin(" ", res, 2);
	return (res);
}
