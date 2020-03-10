/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 09:46:07 by cseguier          #+#    #+#             */
/*   Updated: 2020/03/10 18:11:48 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	print_result(t_p *p, t_path_array *path_array, t_path_combo *path_combo, int lines, int nb_path)
{
	int	id_lines;
	int	id_path;

	id_lines = -1;
	while (++id_lines < lines)
	{
		id_path = -1;
		while (++id_path < nb_path)
		{
			
		}



		ft_printf("\n");
	}


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
	lines /= nb_path;
	ft_printf("final lines: %d\n", lines);
	i = -1;
	while (++i < nb_path)
		path[i].ants = lines - (path[i].size - 2);
	i = -1;
	while (++i < nb_path)
		ft_printf("o> ANTS %d\n", path[i].ants);
	return (lines);
}

int resolve(t_p *p, t_bfs *bfs)
{
	int				shortest_id;
	t_path_combo	*path_combo;
	t_path_combo	*final_combo;
	int				nb_path;
	int				nb_line;
	int				i;

	if (!(path_combo = ft_memalloc(sizeof(t_path_combo) * p->data.ant_count + 1))
		|| !(final_combo = ft_memalloc(sizeof(t_path_combo) * p->data.ant_count + 1)))
		exit_error("Malloc Failed", (char*)__func__);
	i = -1;
	while (++i < p->data.ant_count + 1)
	{
		path_combo[i].ants = -1;
		final_combo[i].ants = -1;
	}
	shortest_id = get_shortest_path(bfs);
	ft_printf("shortest: #%d of %d rooms for %d ants\n", \
		shortest_id, bfs->path_array[shortest_id].size, p->data.ant_count);

	copy_path(bfs, path_combo, 0, 0);
	copy_path(bfs, path_combo, 1, 1);
	nb_path = 2;

	// copy_path(bfs, path_combo, shortest_id, 0);
	// nb_path = 1;

	nb_line = lead_ants(path_combo, p->data.ant_count, nb_path);
	copy_path_combo(final_combo, path_combo);
	ft_printf("++ path_combo ++\n");
	print_combo(p, path_combo);
	ft_printf("++ final_combo ++\n");
	print_combo(p, final_combo);
	ft_printf("\nLines: %d\n", nb_line);
	print_result(p, bfs->path_array, final_combo, nb_line, nb_path);
	return (0);
}
