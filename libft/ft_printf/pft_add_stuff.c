/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pft_add_stuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:01:55 by cseguier          #+#    #+#             */
/*   Updated: 2019/11/13 01:41:33 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*pft_add_preci(char *res, t_pf *p, char c)
{
	int		i;
	char	*it;
	char	*tmp;

	it = NULL;
	i = -1 + ft_strlen(res);
	if (ft_strlen(res) > (unsigned long)p->op_preci && c == 's')
	{
		tmp = ft_strsub(res, 0, p->op_preci);
		ft_memdel((void*)&res);
		res = tmp;
	}
	if (ft_strlen(res) < (unsigned long)p->op_preci && c != 's')
		while (++i < p->op_preci)
			res = ft_strjoin("0", res, 2);
	if ((it = ft_strchr(res, '-')) && (size_t)p->op_preci + 1 > ft_strlen(res))
	{
		it[0] = '0';
		res = ft_strjoin("-", res, 2);
	}
	return (res);
}

char	*pft_add_x(char *res, char c, t_pf *p)
{
	if (!(ft_strcmp(res, "0")) && c != 'p')
	{
		if (p->op_point == 1 && c != 'o')
			res[0] = '\0';
		return (res);
	}
	if (c == 'x' || c == 'p')
		res = ft_strjoin("0x", res, 2);
	if (c == 'X')
		res = ft_strjoin("0X", res, 2);
	if (c == 'o' && res[0] != '0')
		res = ft_strjoin("0", res, 2);
	return (res);
}

char	*pft_add_sign(char *res, t_pf *p)
{
	if (ft_strchr(res, '-'))
		return (res);
	if (p->op_plus == 1 && p->flag != 'u')
		res = ft_strjoin("+", res, 2);
	else if (p->op_space == 1 && p->flag != 'u')
		res = ft_strjoin(" ", res, 2);
	return (res);
}
