/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 11:32:29 by cseguier          #+#    #+#             */
/*   Updated: 2020/02/26 01:41:01 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_putnbr(int nb)
{
	int	max;

	max = 0;
	if (nb < 0)
	{
		if (nb == -2147483648)
		{
			max = 1;
			nb++;
		}
		ft_putchar('-');
		nb = -nb;
	}
	if (nb >= 10)
		ft_putnbr(nb / 10);
	max == 1 ? ft_putchar((nb % 10) + '1') : ft_putchar((nb % 10) + '0');
}
