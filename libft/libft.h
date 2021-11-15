/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:43:55 by fferreir          #+#    #+#             */
/*   Updated: 2021/11/15 19:43:52 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>

typedef struct s_env t_env;

typedef struct s_env
{
	void	*content;
	void	*name;
	t_env	*prev;
	t_env	*next;
}	t_env;

void		*ft_memset(void *str, int c, size_t len);
void		ft_bzero(void *str, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memccpy(void *dst, const void *src, int c, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memchr(const void *str, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
size_t		ft_strlen(const char *str);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
char		*ft_strcpy(char *src, char *dst);
char		*ft_strchr(const char *str, int c);
char		*ft_strrchr(const char *str, int c);
char		*ft_strnstr(const char *haystack, const char *needle,
				size_t len);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_atoi(const char *str);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_toupper(int c);
int			ft_tolower(int c);
int			find_quote(char *s, int i);
void		*ft_calloc(size_t count, size_t size);

char		*ft_strdup(const char *s1);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
char		**ft_split(char const *s, char c);

// Lists
t_env		*ft_envnew(void *content);
void		ft_envadd_front(t_env **lst, t_env *new);
t_env		*ft_envnew(void *content);
t_env		*ft_envdup_2p(t_env *lst);
void		ft_envadd_front(t_env **lst, t_env *new);
int			ft_envsize(t_env *lst);
t_env		*ft_envlast(t_env *lst);
t_env		*ft_envhead_2p(t_env *lst);
void		ft_envadd_back(t_env **lst, t_env *new);
void		ft_envadd_back_2p(t_env **lst, t_env *new);
void		ft_envdelone(t_env *lst, void (*del)(void*));
void		ft_envclear(t_env **lst, void (*del)(void*));
void		ft_enviter(t_env *lst, void (*f)(void*));
t_env		*ft_envmap(t_env *lst, void *(*f)(void*),
				void (*del)(void*));
void		ft_envprint(t_env *lst, char type);
void		ft_envnode_print_2p(t_env *lst);

#endif
