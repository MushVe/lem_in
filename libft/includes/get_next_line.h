/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdidelot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 17:52:36 by fdidelot          #+#    #+#             */
/*   Updated: 2019/11/16 20:11:24 by fdidelot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"

# define GNL_BUFFER_SIZE 1024

typedef struct			s_gnl_lst
{
	int					fd;
	char				*stock;
	struct s_gnl_lst	*next;
}						t_gnl_lst;

int						get_next_line(int fd, char **line);
int						gnl_read(t_gnl_lst *lst);
int						gnl_fill_line(t_gnl_lst *lst, char **line);
t_gnl_lst				*gnl_get_elem(t_gnl_lst **lst, int fd);
char					*gnl_strjoinf(char *s1, char s2[GNL_BUFFER_SIZE]);

#endif
