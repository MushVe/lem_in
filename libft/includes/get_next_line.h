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

# define GNL_BUFF_SIZE 2048

typedef struct	s_gnl
{
	struct s_gnl	*next;
	struct s_gnl	*prev;
	char			*stock;
	int				fd;
}				t_gnl;

char			*ft_gnl_strjoin2(char const *s1, char const *s2);
char			*ft_gnl_strjoinf(char *s1, char *s2);

#endif
