/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 16:39:05 by cseguier          #+#    #+#             */
/*   Updated: 2020/02/26 01:41:07 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

static void	swap(t_path_array *a, t_path_array *b)
{
	t_path_array c;

	c = *b;
	*b = *a;
	*a = c;
}

static void	sort(t_path_array *array, int array_size)
{
	int	low;
	int	i;
	int	pivot;

	if (array_size < 2)
		return ;
	pivot = array[array_size - 1].size;
	low = 0;
	i = 0;
	while (i < array_size)
	{
		if (array[i].size <= pivot)
		{
			if (low != i)
				swap(&array[i], &array[low]);
			low++;
		}
		i++;
	}
	sort(array, low - 1);
	sort(array + low - 1, array_size - low + 1);
}

void		quicksort(t_bfs *bfs)
{
	sort(bfs->path_array, bfs->path_nb);
}
