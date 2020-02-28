// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   gnl_strjoin.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2019/11/17 02:37:56 by cseguier          #+#    #+#             */
// /*   Updated: 2020/02/26 01:43:05 by cseguier         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// //#include "../includes/libft.h"

// char	*ft_gnl_strjoin2(char const *s1, char const *s2)
// {
// 	int		i;
// 	char	*str;

// 	if (s1 == NULL && s2 == NULL)
// 		return ((char *)NULL);
// 	if (s1 == NULL && s2)
// 		return (ft_strdup(s2));
// 	if (s1 && s2 == NULL)
// 		return (ft_strdup(s1));
// 	i = ft_strlen(s1) + ft_strlen(s2);
// 	if ((str = ft_strnew(i)) == NULL)
// 		return (NULL);
// 	i = 0;
// 	str = ft_strcpy(str, s1);
// 	str = ft_strcat(str, s2);
// 	return (str);
// }

// char	*ft_gnl_strjoinf(char *s1, char *s2)
// {
// 	int		i;
// 	char	*str;

// 	if (s1 == NULL && s2 == NULL)
// 		return ((char *)NULL);
// 	if (s1 == NULL && s2)
// 		return (ft_strdup(s2));
// 	if (s1 && s2 == NULL)
// 		return (ft_strdup(s1));
// 	i = ft_strlen(s1) + ft_strlen(s2);
// 	if ((str = ft_strnew(i)) == NULL)
// 		return (NULL);
// 	i = 0;
// 	str = ft_strcpy(str, s1);
// 	ft_memdel((void*)&s1);
// 	str = ft_strcat(str, s2);
// 	return (str);
// }
