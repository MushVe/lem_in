/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 09:46:07 by cseguier          #+#    #+#             */
/*   Updated: 2020/03/09 17:54:45 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int	get_shortest_path(t_bfs *bfs)
{
	int	path_id;
	int	shortest;
	int	res;

	path_id = -1;
	shortest = __INT_MAX__;
	while (++path_id < bfs->path_nb)
	{
		if (bfs->path_array[path_id].size < shortest)
		{
			shortest = bfs->path_array[path_id].size;
			res = path_id;
		}
	}
	return (res);
}

void	copy_path(t_bfs *bfs, t_path_combo **path_combo, int id)
{
	
	while (/* condition */)
	{
		/* code */
	}
	
}

void	copy_path_combo()
{

}

int resolve(t_p *p, t_bfs *bfs)
{
	int				shortest_id;
	int				final_path;
	// conditions d'arret: (x_combo[i].ants != -1 && ++i < p->data.ant_count)
	t_path_combo	*path_combo;
	t_path_combo	*final_combo;
	int				nb_lignes;
	int				i;

	if (!(path_combo = ft_memalloc(sizeof(t_path_combo) * p->data.ant_count)))
		exit_error("Malloc Failed", (char*)__func__);
	i = -1;
	while (++i < p->data.ant_count)
		path_combo[i].ants = -1;
	shortest_id = get_shortest_path(bfs);
	ft_printf("shortest: #%d of %d rooms\n", \
		shortest_id, bfs->path_array[shortest_id].size);

	copy_path(bfs, &path_combo, shortest_id);
	copy_path_combo(&final_combo, path_combo);

	print_result(bfs->path_array, final_combo, p->data.ant_count, nb_lignes);

	return (0);
}

void	print_result(t_path_array *path_array, t_path_combo *path_combo, int ants, int lines)
{
	int	id_ants;
	int	id_lines;

	id_lines = -1;
	while (++id_lines < lines)
	{
		
		while (path_combo != -1 && ++id_ants < ants)
		{
			ft_printf("L%d-%d", id_ants, path_array[path_combo[id_ants]]);
		}
	}
}

/*

while (ants in maze)
while (paths in solution)
while (rooms in path)


[start] --- [A] --- [B] --- [end]
3> 2> 1>                         
3> 2>       1>                   
3>          2>      1>           
            3>      2>      1>   
                    3>      2> 1>
                            3> 2> 1>

L1-A
L1-B   L2-A
l1-end L2-B l3-A
L2-end L3-B
L3-end


3 o>
      [start]
      /    \
    [A]   [B]
     |     |
     |    [C]
     \    /
     [end]

L1-A   L2-B
L1-end L3-A   L2-C
L3-end L2-end

*/

/*
	nb_chmin_max = nb_fourmis

	int	tab[nb_chemin] = ((nb_fourmi / nb_chemin) + taille_chemin) 
	ex : 100 fourmis 4 chemins (10 12 14 16)
	25 + 10 = 35
	25 + 12 = 37
	25 + 14 = 39
	25 + 16 = 41
	++++++++++++++++MOYENNE+++++++++++++++++++++
	(35 + 37 + 39 + 41) / 4 =
							= 152 / 4 =
									= 38
	==> 38 lignes d'envoi 
	==> (38 - taille_chemin) fourmis par chemin
	38 - 10 = 28
	38 - 12 = 26
	38 - 14 = 24
	38 - 16 = 22

tab[0] = (4 / 2) + 5
tab[1] = (4 / 2) + 5
2 + 5 = 7
2 + 5 = 7
(7 + 7) / 2 = 7

tab[0] = (4 / 1) + 4
4 + 4 = 8

[0]-[1]-[4]
[0]-[2]-[3]-[4]

tab[0] = (2 / 2) + 3
tab[1] = (2 / 2) + 4
1 + 3 = 4
1 + 4 = 5
(4 + 5) / 2 = 5

tab[0] = (2 / 1) + 3
2 + 3 = 5

tab[0] = (2 / 1) + 4
2 + 4 = 6

*/