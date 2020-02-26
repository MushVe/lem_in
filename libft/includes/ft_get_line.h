/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_line.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 01:35:38 by cseguier          #+#    #+#             */
/*   Updated: 2020/02/26 05:41:32 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GET_LINE_H
# define FT_GET_LINE_H

# include <stdbool.h>
# include "libft.h"

# define BUFFA_SIZE 1000000

typedef struct	s_func_list
{
	struct func_list	*next;
	void				(*my_strjoin)(char **, char *);
}				t_f_list;

bool			is_storage_empty(char *storage);
bool			contain_new_line(char *data, char **new_line_pos);
bool			is_nl_last_char(char *data, char *new_line_pos);
bool			save_data(char **storage, char *buffer);
void			strjoin_free_s1(char **s1, char *s2);
int				ft_get_line(int fd, char **line, char **storage);

#endif
