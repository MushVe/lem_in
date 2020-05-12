/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 17:13:11 by cseguier          #+#    #+#             */
/*   Updated: 2020/03/11 16:00:22 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdbool.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/uio.h>

/*
** QUEUE
*/

typedef struct	s_qnode
{
	int				data;
	struct s_qnode	*next;
}				t_qnode;

typedef struct	s_queue
{
	t_qnode	*front;
	t_qnode	*rear;
}				t_queue;

t_queue			*create_queue(void);
void			en_queue(t_queue *q, int data);
void			de_queue(t_queue *q);

/*
** LIBFT
*/

typedef struct	s_lftlist
{
	void				*content;
	size_t				content_size;
	struct s_lftlist	*next;
}				t_lftlist;

int				ft_atoi(char const *str);
int				ft_abs(int nb);
void			ft_bzero(void *s, size_t n);
char			*ft_capitalize(char *str);
void			ft_doublefree(char **s);
void			ft_doublefree_int(int **s, int size);
void			ft_doubleprint(char **s);
void			ft_foreach(int *tab, size_t lenght, void (*f)(int));
int				get_next_line(int const fd, char **line);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
char			*ft_itoa(int n);
char			*ft_itoa_base(unsigned long long nb, int base, int alpha);
char			*ft_lowcase(char *str);
void			ft_lstadd(t_lftlist **alst, t_lftlist *link);
void			ft_lstdel(t_lftlist **alst, void (*del)(void *, size_t));
void			ft_lstdelone(t_lftlist **alst, void(*del)(void*, size_t));
void			ft_lstiter(t_lftlist *lst, void (*f)(t_lftlist *elem));
t_lftlist		*ft_lstmap(t_lftlist *lst, t_lftlist *(*f)(t_lftlist *elem));
t_lftlist		*ft_lstnew(void const *content, size_t content_size);
void			*ft_memalloc(size_t size);
void			*ft_memccpy(void *dest, void const *src, int c, size_t n);
void			*ft_memchr(void const *s, int c, size_t n);
int				ft_memcmp(void const *s1, void const *s2, size_t n);
void			*ft_memcpy(void *dest, void const *src, size_t n);
void			ft_memdel(void **ap);
void			*ft_memmove(void *dest, void const *src, size_t n);
void			*ft_memset(void *s, int c, size_t n);
double			ft_pow(double x, int y);
void			ft_putchar(char c);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl(char const *s);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr(int nb);
void			ft_putnbr_fd(int nb, int fd);
void			ft_putnstr(char const *s, int n);
void			ft_putstr(char const *s);
void			ft_putstr_fd(char const *s, int fd);
char			*ft_quicksort(char const *s, size_t len);
int				ft_round(int dividentd, int divisor);
int				ft_sqrt(int nb);
char			*ft_strcat(char *dest, char const *src);
char			*ft_strccpy(char *dest, char const *src, char c);
char			*ft_strcdup(char const *src, char c);
char			*ft_strchr(char const *s, int c);
void			ft_strclr(char *s);
int				ft_strcmp(char const *s1, char const *s2);
char			*ft_strcpy(char *dest, char const *src);
void			ft_strdel(char **as);
char			*ft_strdup(char const *src);
char			*ft_strndup(char const *src, int n);
int				ft_strequ(char const *s1, char const *s2);
char			*ft_stricpy(char *dest, int it, char const *src);
char			*ft_stridup(char const *src, int it);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strjoin(char *s1, char *s2, int id);
size_t			ft_strlcat(char *dest, char const *src, size_t size);
size_t			ft_strlen(char const *str);
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_strncat(char *dest, char const *src, size_t n);
int				ft_strncmp(char const *s1, char const *s2, size_t n);
char			*ft_strncpy(char *dest, char const *src, size_t n);
int				ft_strnequ(char const *si, char const *s2, size_t n);
char			*ft_strnew(size_t size);
char			*ft_strnstr(char const *str, char const *need, size_t len);
char			*ft_strrchr(char const *s, int c);
char			*ft_strrev(char const *str, size_t len);
char			**ft_strsplit(char const *s, char c);
char			*ft_strstr(char const *str, char const *need);
char			*my_strtok(char *line, int *end);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strtrim(char const *s);
int				ft_tolower(int c);
int				ft_toupper(int c);
char			*ft_upcase(char *str);

#endif
