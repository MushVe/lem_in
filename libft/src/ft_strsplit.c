/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 15:45:38 by cseguier          #+#    #+#             */
/*   Updated: 2020/03/06 05:30:50 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i] == c && s[i])
		i++;
	if (s[i] != '\0')
	{
		words++;
		while (s[i] != '\0')
		{
			if (s[i + 1] != '\0' && s[i] == c && s[i + 1] != c)
				words++;
			i++;
		}
	}
	return (words);
}

static int	*count_letters(char const *s, char c, int *words_numbers)
{
	int	i;
	int	letters;
	int	*array;
	int	j;

	i = 0;
	j = 0;
	letters = 0;
	if (!(array = (int*)malloc(*words_numbers * sizeof(int))))
		return (NULL);
	while (s[i] != '\0' && s[i] == c)
		i++;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i++] != c)
			letters++;
		while (s[i] != '\0' && s[i] == c)
			i++;
		array[j] = letters;
		letters = 0;
		j++;
	}
	return (array);
}

static void	dimensional_copy(char const *s, char c, char **dest)
{
	int	i;
	int	j;
	int	z;

	i = 0;
	j = 0;
	z = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		while (s[i] != '\0' && s[i] != c)
			dest[z][j++] = s[i++];
		while (s[i] != '\0' && s[i] == c)
			i++;
		i--;
		dest[z][j] = '\0';
		j = 0;
		i++;
		z++;
	}
	dest[z] = 0;
}

char		**ft_strsplit(char const *s, char c)
{
	int		i;
	int		*tab;
	int		words_numbers;
	char	**new_strings;

	i = -1;
	if (!s)
		return (NULL);
	words_numbers = count_words(s, c);
	if (!(tab = count_letters(s, c, &words_numbers)))
		return (NULL);
	if (!(new_strings = ft_memalloc((words_numbers + 1) * sizeof(char*))))
		return (0);
	while (++i < words_numbers)
		if (!(new_strings[i] = ft_memalloc((tab[i] + 1) * sizeof(char))))
			return (0);
	dimensional_copy(s, c, new_strings);
	free(tab);
	return (new_strings);
}

/*
**  static int	ft_nstr(char const *str, char c)
**  {
**  int	nb;
**  int	res;
**  int	i;
**
**  res = 0;
**  i = 0;
**  nb = 1;
**  while (str[i] != '\0')
**  {
**  while (str[i] != '\0' && str[i] == c)
**  {
**  i++;
**  nb++;
**  }
**  while (str[i] != '\0' && str[i] != c)
**  {
**  i++;
**  if (nb)
**  {
**  res++;
**  nb = 0;
**  }
**  }
**  }
**  return (res);
**  }
**
**  static char	**ft_loop(char **tab, char *str, int j, char c)
**  {
**  int	ccmot;
**  int	x;
**  int	i;
**
**  i = 0;
**  while (str[i] != '\0')
**  {
**  ccmot = 0;
**  while (str[i] != '\0' && str[i] == c)
**  i++;
**  while (str[i] != '\0' && str[i] != c)
**  {
**  i++;
**  ccmot++;
**  }
**  if (ccmot && !(tab[j] = (char*)ft_memalloc(sizeof(char) * (ccmot))))
**  return (NULL);
**  x = -1;
**  while (ccmot > ++x)
**  tab[j][x] = str[i - ccmot + x];
**  if (ccmot && ++j > 0)
**  tab[j - 1][x] = '\0';
**  tab[j] = 0;
**  }
**  return (tab);
**  }
**
**  char		**ft_strsplit(char const *s, char c)
**  {
**  int		j;
**  char	**tab;
**
**  j = 0;
**  if (!s)
**  return (NULL);
**  if (!(tab = (char**)ft_memalloc(sizeof(char*) * (ft_nstr(s, c) + 1))))
**  return (NULL);
**  if (!(tab = ft_loop(tab, (char*)s, j, c)))
**  return (NULL);
**  return (tab);
** }
*/
