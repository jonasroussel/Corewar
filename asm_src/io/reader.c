/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 12:01:26 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/28 14:19:25 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_bool	open_file(t_asm *env, t_prog *prog)
{
	char	*error;

	if ((env->fd = open(prog->file, O_RDONLY | O_EXLOCK)) < 0)
	{
		if (!(error = strerror(errno)))
			quit(env, MALLOC_ERROR);
		ft_printf("%s: {lred}{bold}error:{reset} %s\n", prog->file, error);
		return (FALSE);
	}
	return (TRUE);
}

static t_bool	isvalid(char *content, ssize_t len)
{
	ssize_t	i;

	i = 0;
	while (i < len)
	{
		if (content[i] == '\0')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static int		read_content(t_asm *env, t_prog *prog)
{
	char	buff[READ_SIZE];
	char	*last;
	ssize_t	len;

	if (!(prog->content = ft_strnew(0)))
		quit(env, MALLOC_ERROR);
	while ((len = read(env->fd, buff, READ_SIZE - 1)) > 0)
	{
		buff[len] = '\0';
		if (!isvalid(buff, len))
		{
			ft_memdel((void **)&prog->content);
			ft_printf("%s: {lred}{bold}error:{reset} %s\n", prog->file,
				INVALID_FILE);
			return (0);
		}
		last = prog->content;
		if (!(prog->content = ft_strjoin(prog->content, buff)))
			quit(env, MALLOC_ERROR);
		free(last);
	}
	return (len < 0 ? -1 : 1);
}

t_bool			reader(t_asm *env, t_prog *prog)
{
	char	*error;
	int		ret;

	if (!open_file(env, prog))
		return (FALSE);
	ret = read_content(env, prog);
	if (ret < 0)
	{
		if (!(error = strerror(errno)))
			quit(env, MALLOC_ERROR);
		ft_memdel((void **)&prog->content);
		ft_printf("%s: {lred}{bold}error:{reset} %s\n", prog->file, error);
		return (FALSE);
	}
	else if (ret == 0)
		return (FALSE);
	if (prog->content[0] == '\0')
	{
		ft_memdel((void **)&prog->content);
		ft_printf("%s: {lred}{bold}error:{reset} %s\n", prog->file, EMPTY_FILE);
		return (FALSE);
	}
	prog->header->magic = COREWAR_EXEC_MAGIC;
	return (TRUE);
}
