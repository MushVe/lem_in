/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pft_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:01:55 by cseguier          #+#    #+#             */
/*   Updated: 2019/11/13 01:46:11 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		get_type(t_pf *p, char c)
{
	if (c == 'h')
	{
		if (p->op_type != 0 && p->op_type != 11)
			return (1);
		if (p->op_type == 0)
			p->op_type += 10;
	}
	if (c == 'l')
	{
		if (p->op_type != 0 && p->op_type != 21)
			return (1);
		if (p->op_type == 0)
			p->op_type += 20;
	}
	if (c == 'L')
	{
		if (p->op_type != 0 && p->op_type != 31)
			return (1);
		if (p->op_type == 0)
			p->op_type += 30;
	}
	p->op_type += 1;
	return (0);
}

int		getoptions(t_pf *p, const char *frmt)
{
	if (frmt[0] == '+')
		p->op_plus = 1;
	else if (frmt[0] == '-')
		p->op_less = 1;
	else if (frmt[0] == ' ')
		p->op_space = 1;
	else if (frmt[0] == '#')
		p->op_diese = 1;
	else if (frmt[0] == '0' && p->op_width == 0 && p->op_preci == 0
				&& p->op_point == 0)
		p->op_zero = 1;
	else if (frmt[0] == '.')
		p->op_point = 1;
	else if (ft_isdigit(frmt[0]) && p->op_point == 0 && p->op_width == 0)
		p->op_width = ft_atoi(frmt);
	else if (ft_isdigit(frmt[0]) && p->op_point == 1 && p->op_preci == 0)
		p->op_preci = ft_atoi(frmt);
	else if (frmt[0] == 'h' || frmt[0] == 'l' || frmt[0] == 'L')
		get_type(p, frmt[0]);
	else if (!(ft_isdigit(frmt[0]) && p->op_type == 0
			&& (p->op_width != 0 || p->op_preci != 0)))
		return (0);
	return (1);
}

static int		ptf_fonction(char *frmt, t_pf *p, int *i, va_list ap)
{
	while (!(pft_isflag(frmt[i[0]], p)) && pft_isoption(frmt[i[0]]))
	{
		if (!(getoptions(p, frmt + i[0])))
			return (0);
		i[0]++;
	}
	if (!(pft_isflag(frmt[i[0]], p)))
		i[0]--;
	ptf_process(frmt[i[0]], ap, p);
	i[2] = 1;
	i[1] = i[0] + 1;
	return (1);
}

int		get_everything(char *frmt, t_pf *p, int *i, va_list ap)
{
	while (frmt[++i[0]])
	{
		ptf_init(p);
		if (i[2] == 1 && (frmt[i[0]] == '%' || frmt[i[0]] == '\0'))
		{
			i[2] = 0;
			if (i[1] != i[0])
				if (!(ptf_new_node(ft_stridup(frmt + i[1], i[0] - i[1]),
					i[0] - i[1], p)))
					return (0);
		}
		else if (i[2] == 0)
		{
			if (!(ptf_fonction(frmt, p, i, ap)))
				return (0);
		}
	}
	return (1);
}

int		ptf_parser(const char *restrict frmt, t_pf *p, va_list ap)
{
	int	i[3];

	i[0] = -1;
	i[1] = 0;
	i[2] = 1;
	if (!(get_everything((char *)frmt, p, i, ap)))
		return (0);
	if (i[1] != i[0] && frmt[i[0] - 1] != '%')
		if (!(ptf_new_node(ft_stridup(frmt + i[1], i[0] - i[1]),
			i[0] - i[1], p)))
			return (0);
	i[0] = ptf_print_node(p);
	return (i[0]);
}
