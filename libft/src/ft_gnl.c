/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 10:31:06 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/28 14:20:59 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*get_file(t_list **files, const int fd)
{
	t_list	*file;

	file = *files;
	while (file != NULL)
	{
		if (file->size == (size_t)fd)
			return (file);
		file = file->next;
	}
	if (!(file = ft_lstnew("\0", 1)))
		return (NULL);
	file->size = (size_t)fd;
	ft_lstadd(files, file);
	return (file);
}

static char		*opcut(char **content)
{
	char	*indexp;
	char	*cut;
	char	*tmp;

	indexp = ft_strchr(*content, SPLITTER);
	if (indexp == NULL)
		return (NULL);
	if (!(cut = ft_strsub(*content, 0, indexp - (*content))))
		return ((char *)0x2a);
	tmp = *content;
	if (!(*content = ft_strsub(*content, indexp - (*content) + 1, 0)))
		return ((char *)0x2a);
	free(tmp);
	return (cut);
}

static int		process(t_list *file, char **line)
{
	char	*tmp;

	if ((tmp = opcut((char **)(&file->content))) != NULL)
	{
		if (tmp == (char *)0x2a)
			return (-1);
		*line = tmp;
		return (ft_strlen(*line));
	}
	return (0);
}

static int		read_file(const int fd, t_list *file)
{
	char	buff[BUFF_SIZE + 1];
	ssize_t	len;
	char	*tmp;

	while ((len = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[len] = '\0';
		tmp = (char *)file->content;
		if (!(file->content = ft_strjoin(tmp, buff)))
			return (-1);
		free(tmp);
		if ((tmp = ft_strchr(buff, SPLITTER)) != NULL || len < BUFF_SIZE)
			break ;
	}
	if (len == -1 || (len < BUFF_SIZE && !ft_strlen((char *)file->content)))
		return (len == -1 ? -1 : 0);
	return (1);
}

int				ft_gnl(const int fd, char **line)
{
	static t_list	*files = NULL;
	t_list			*file;
	int				tmp;

	if (fd == CLEAR)
	{
		ft_lstdel(&files, TRUE);
		return (0);
	}
	if ((file = get_file(&files, fd)) == NULL)
		return (-1);
	if (file->content == NULL)
		return (0);
	if ((tmp = process(file, line)))
		return (tmp);
	if ((tmp = read_file(fd, file)) < 1)
		return (tmp);
	if ((tmp = process(file, line)))
		return (tmp);
	*line = ft_strdup((char *)file->content);
	ft_strdel((char **)(&file->content));
	return (ft_strlen(*line));
}
