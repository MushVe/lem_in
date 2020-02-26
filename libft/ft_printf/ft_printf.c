/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:01:55 by cseguier          #+#    #+#             */
/*   Updated: 2019/11/27 02:47:27 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
**	void	va_start(va_list ap, last);
**	type	va_arg(va_list ap, type);
**	void	va_copy(va_list dest, va_list src);
**	void	va_end(va_list ap);
*/

int		ptf_print_node(t_pf *p)
{
	t_lst	*cpy;
	int		i;

	cpy = p->first;
	i = 0;
	while (cpy)
	{
		ft_putstr(cpy->str);
		i = i + ft_strlen(cpy->str);
		if (cpy->null == 1)
		{
			write(1, "\0", 1);
			i++;
		}
		cpy = cpy->next;
	}
	return (i);
}

void	ptf_init(t_pf *p)
{
	p->op_plus = 0;
	p->op_less = 0;
	p->op_space = 0;
	p->op_diese = 0;
	p->op_zero = 0;
	p->op_preci = 0;
	p->op_point = 0;
	p->op_width = 0;
	p->op_type = 0;
	p->flag = 0;
	p->null = 0;
}

int		ft_printf(const char *restrict format, ...)
{
	t_pf	p;
	va_list	ap;
	int		i;

	va_start(ap, format);
	p.first = NULL;
	i = ptf_parser(format, &p, ap);
	ptf_free_list(&p.first);
	return (i);
}
