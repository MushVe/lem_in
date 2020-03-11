/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 09:46:07 by cseguier          #+#    #+#             */
/*   Updated: 2020/03/11 18:20:38 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	fill_ants_by_rooms(int **ants, t_path_combo *path, int nb_path)
{
	int	path_id;

	path_id = -1;
	if (!(*ants = ft_memalloc(sizeof(int) * nb_path)))
		exit_error("Malloc Failed", (char*)__func__);
	while (++path_id < nb_path)
		(*ants)[path_id] = path[path_id].ants;
}

void	print_result(t_p *p, t_path_array *path_array, t_path_combo *path_combo, int lines, int nb_path)
{
	int	lines_id;
	int	path_id;
	int	ant_cpt;
	int	*ants_by_rooms;

	fill_ants_by_rooms(&ants_by_rooms, path_combo, nb_path);

	path_id = -1;
	while (++path_id < nb_path)
		ft_printf("Ants: %d in Room #%d\n", ants_by_rooms[path_id], path_id);
	

	// path_id = -1;
	// while (++path_id < nb_path)
	// {
	// 	while (path_combo[path_id].ants)
	// 	{
			
	// 	}
	// }



		ft_printf("\n");


}

int		lead_ants(t_path_combo *path, int ants, int nb_path)
{
	int	lines;
	int	i;

	lines = 0;
	i = -1;

	while (++i < nb_path)
	{
		ft_printf("Line #%d = %d\n", i, (ants / nb_path) + path[i].size - 2);
		lines += (ants / nb_path) + path[i].size - 2;
	}
	ft_printf("after line: %d\n", lines);
	lines = ft_round(lines, nb_path);
	ft_printf("final lines: %d\n", lines);
	i = -1;
	while (++i < nb_path)
		path[i].ants = lines - (path[i].size - 2);
	i = -1;
	while (++i < nb_path)
		ft_printf("o> ANTS %d for ROOM #%d\n", path[i].ants, i);
	return (lines);
}

void	init_res(t_path_combo **path_combo, int ant)
{
	int	i;

	if (!(*path_combo = ft_memalloc(sizeof(t_path_combo) * ant + 1)))
		exit_error("Malloc Failed", (char*)__func__);
	i = -1;
	while (++i < ant + 1)
		(*path_combo)[i].ants = -1;
}

void	clear_path_combo(t_path_combo *path_combo, int ant)
{
	int	i;

	i = -1;
	while (++i < ant + 1)
	{
		path_combo[i].ants = -1;
		path_combo[i].size = -1;
		ft_memdel((void*)&path_combo[i].room);
	}
}

int	get_shortest_combo(t_p *p, t_bfs *bfs, t_path_combo *path_combo)
{
	t_path_combo	*best_combo;
	int				shortest_id;
	int				nb_line;
	int				path_id;

	// get short paths (increasing) no-colinding
	// get nb_line for each combo
	// keep smallest nb_line as valid w/ best_combo
	// clear path_combo and try another
	// arbitrary number of tries
	// path number in combo limited by ants number
	// should be good

	while ()
	{

	}






	return (nb_line);
	// shortest_id = get_shortest_path(bfs);
	// ft_printf("\nshortest: #%d of %d rooms for %d ants\n", \
	// 	shortest_id, bfs->path_array[shortest_id].size, p->data.ant_count);
}

int resolve(t_p *p, t_bfs *bfs)
{
	t_path_combo	*path_combo;
	int				nb_path;
	int				nb_line;

	init_res(path_combo, p->data.ant_count);

	nb_path = get_shortest_combo(p, bfs, path_combo);
	nb_line = lead_ants(path_combo, p->data.ant_count, nb_path);

	ft_printf("\n++ total lines {%d} ants {%d} ++\n", nb_line, p->data.ant_count);
	print_combo(p, path_combo);
	ft_printf("\n");
	print_result(p, bfs->path_array, path_combo, nb_line, nb_path);
	return (0);
}


	// copy_path(bfs, path_combo, 0, 0);
	// copy_path(bfs, path_combo, 1, 1);
	// copy_path(bfs, path_combo, shortest_id, 2);
	// nb_path = 3;

//	copy_path(bfs, path_combo, shortest_id, 0);
//	nb_path = 1;