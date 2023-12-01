/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 14:19:23 by jroussel          #+#    #+#             */
/*   Updated: 2019/02/01 13:40:30 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*add_extension(char *name)
{
	char	*new;
	size_t	len;
	size_t	i;
	size_t	point;

	len = ft_strlen(name);
	i = len - 1;
	point = len;
	while (i > 0)
	{
		if (name[i] == '.' && (point = i))
			break ;
		i--;
	}
	if (!(new = ft_strnew(len + (point == len ? 4 : 2) + 1)))
		return (NULL);
	ft_strcpy(new, name);
	ft_strcpy(new + len - (point == len ? 0 : 2), ".cor");
	return (new);
}

static char	*basic_output(t_asm *env, char *file)
{
	char	*output;
	char	*name;

	if (!(name = add_extension(basename(file))))
		return (NULL);
	if (!(output = ft_strnew(ft_strlen(env->output) + ft_strlen(name) + 1)))
		return (NULL);
	ft_strcpy(output, env->output);
	ft_strcat(output, "/");
	ft_strcat(output, name);
	free(name);
	return (output);
}

static char	*recursive_output(t_asm *env, char *file)
{
	char	*output;
	char	*dir;
	char	*name;
	char	*start;

	dir = dirname(file);
	name = add_extension(basename(file));
	if (!(output = ft_strnew(ft_strlen(env->output) + ft_strlen(dir)
			+ ft_strlen(name) + 2)))
		return (NULL);
	ft_strcpy(output, env->output);
	start = ft_strchr(dir, '/');
	if (start)
		mkdir_p(env, ft_strcat(output, start));
	free(dir);
	ft_strcat(output, "/");
	ft_strcat(output, name);
	free(name);
	return (output);
}

char		*make_output(t_asm *env, char *file)
{
	if (env->flags & FLAG_OUTPUT)
	{
		if (env->flags & FLAG_RECURSIVE)
			return (recursive_output(env, file));
		return (basic_output(env, file));
	}
	return (add_extension(file));
}
