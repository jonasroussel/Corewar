/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroussel <jroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 20:18:28 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/03 12:10:56 by jroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <inttypes.h>

# define BUFF_SIZE		1024
# define SPLITTER		'\n'
# define CLEAR			-0x2a

# define TRUE			1
# define FALSE			0

typedef unsigned char	t_byte;
typedef unsigned char	t_bool;

typedef struct			s_list
{
	void			*content;
	size_t			size;
	struct s_list	*next;
}						t_list;

/*
** Memory
*/
void					*ft_memset(void *mem, const t_byte byte,
									const size_t size);
void					*ft_memput(void *mem, const intmax_t data,
									const uint8_t size, const size_t amount);
void					ft_bzero(void *mem, const size_t size);
void					*ft_memcpy(void *dest, const void *src,
									const size_t size);
void					*ft_memccpy(void *dest, const void *src,
									const t_byte byte, const size_t size);
void					*ft_memchr(void *mem, const t_byte byte,
									const size_t size);
int						ft_memcmp(const void *m1, const void *m2,
									const size_t size);
void					*ft_memalloc(const size_t size);
void					ft_memdel(void **ptr);

/*
** String
*/
size_t					ft_strlen(const char *str);
char					*ft_strdup(const char *str);
char					*ft_strcpy(char *dest, const char *src);
char					*ft_strncpy(char *dest, const char *src,
									const size_t size);
char					*ft_strcat(char *dest, const char *src);
char					*ft_strncat(char *dest, const char *src,
									const size_t size);
char					*ft_strchr(const char *str, const char c);
char					*ft_strrchr(const char *str, const char c);
char					*ft_strstr(const char *str, const char *search);
char					*ft_strnstr(const char *str, const char *search,
									const size_t size);
int						ft_strcmp(const char *s1, const char *s2);
int						ft_strncmp(const char *s1, const char *s2,
									const size_t size);
char					*ft_strnew(const size_t size);
void					ft_strdel(char **ptr);
void					ft_strclr(char *str);
void					ft_striter(char *str, void (*f)(char *));
char					*ft_strsub(const char *str, const unsigned int start,
									const size_t size);
char					*ft_strjoin(const char *s1, const char *s2);
char					*ft_strtrim(const char *str);
char					**ft_strsplit(const char *str, const char c);
void					ft_strsplitdel(char ***split);
void					ft_strupper(char *str);
void					ft_strlower(char *str);
void					ft_strcap(char *str);
void					ft_strreplace(char *str, const char c, const char r);

/*
** List
*/
t_list					*ft_lstnew(const void *content, const size_t size);
void					ft_lstdel(t_list **plist, t_bool force);
size_t					ft_lstlen(t_list *list);
void					ft_lstadd(t_list **plist, t_list *new);
void					ft_lstaddi(t_list **plist, t_list *new,
									const unsigned int index);
void					ft_lstpush(t_list **plist, t_list *new);
void					ft_lstremove(t_list **plist, t_list *node);
t_bool					ft_lstctn(t_list *list, const void *content);
t_list					*ft_lstget(t_list *list, const unsigned int index);
void					ft_lstiter(t_list *list, void (*f)(t_list *node));

/*
** Writers
*/
int						ft_printf(const char *format, ...);

/*
** Testers
*/
t_bool					ft_isblank(const char c);
t_bool					ft_islower(const char c);
t_bool					ft_isupper(const char c);
t_bool					ft_isalpha(const char c);
t_bool					ft_isdigit(const char c);
t_bool					ft_isalnum(const char c);
t_bool					ft_isascii(const char c);
t_bool					ft_isprint(const char c);
t_bool					ft_isnl(const char c);
t_bool					ft_isnumber(const char *str);
t_bool					ft_equal(const char *s1, const char *s2);

/*
** Maths
*/
double					ft_pow(double nbr, uint8_t pow);

/*
** Converters
*/
long					ft_atol(const char *str);
char					*ft_ltoa(intmax_t nbr);
char					*ft_ultoa(uintmax_t nbr);
char					*ft_ultoa_base(uintmax_t nbr, const uint8_t base);
char					ft_toupper(char c);
char					ft_tolower(char c);

/*
** Reader
*/
int						ft_gnl(const int fd, char **line);

#endif
