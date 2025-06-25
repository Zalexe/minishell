/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 13:51:30 by cmarrued          #+#    #+#             */
/*   Updated: 2025/06/19 17:23:37 by intherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdint.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_list_wrapper
{
	t_list	*first;
	t_list	*last;
	int		size;
}	t_list_w;

/* INICIAR FUNCIONES */
int		ft_atoi(const char *str);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_memcmp(void *s1, void *s2, size_t n);
int		ft_strncmp(char *s1, const char *s2, size_t n);
size_t	ft_strlcat(char *dest, const char *src, size_t nb);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *c);
void	ft_bzero(void *s, size_t size);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memchr(void *s, int c, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t size);
void	*ft_memmove(void *dest, const void *src, size_t size);
void	*ft_memset(void *s, int c, size_t size);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int nb, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strchr(const char *str, int c);
char	*ft_strdup(const char *s);
char	*ft_strndup(const char *s, size_t n);
char	*ft_strnstr(const char *str, const char *to_find, size_t len);
char	*ft_strrchr(const char *str, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	**ft_split(char const *str, char c);

int		ft_lstsize(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *nw);
void	ft_lstadd_back(t_list **lst, t_list *nw);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));

// ft_printf
int		ft_printf(char const *format, ...);
int		ft_printstr(char *str);
int		ft_printchar(char c);
int		ft_printnbr(int nb);
int		ft_putnbr_unsigned(unsigned int n);
int		ft_putnbr_hex(unsigned long n, int uppercase);
int		ft_putpointer(unsigned long nb);
int		handle_conversion(va_list args, char c);

//getn next line
char	*get_next_line(int fd);
char	*append_buffer(char *b_buffer, char *read_buffer);
char	*extract_line(char *b_buffer);
char	*obtain_remain(char *b_buffer);
char	*read_from_file(char *b_buffer, int fd);

// Wrapper stuff
void	lst_init(t_list_w *list);
t_list	*lst_add(t_list_w *list, void *item);
t_list	*lst_addbefore(t_list_w *list, void *item, t_list *before);
t_list	*lst_addfirst(t_list_w *list, void *item);
void	*lst_clear(t_list_w *list, void (*del)(void *));

#endif
