/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_round.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 15:22:53 by cseguier          #+#    #+#             */
/*   Updated: 2020/04/24 18:38:12 by cseguier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_round(int dividend, int divisor)
{
	if (divisor == 0)
	{
		ft_putendl("           ><\n         | __)  kya\n     \
.-^^| |\n  __|      |\n <__.|_|-|_|");
		return (0);
	}
	return ((dividend + (divisor / 2)) / divisor);
}
