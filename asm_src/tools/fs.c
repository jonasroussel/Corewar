/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fs.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 14:43:41 by jroussel          #+#    #+#             */
/*   Updated: 2019/02/01 13:37:52 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char		*basename(char *file)
{
	char	*start;

	start = ft_strrchr(file, '/');
	if (!start)
		return (file);
	else
		return (start + 1);
}

char		*dirname(char *file)
{
	char	*end;

	end = ft_strrchr(file, '/');
	if (!end)
		return (ft_strdup("."));
	else
		return (ft_strsub(file, 0, end - file));
}

static void	mkwhile(t_asm *env, char *dir, char **p)
{
	while (**p)
	{
		if (**p == '/')
		{
			**p = '\0';
			if (mkdir(dir, 0777))
			{
				if (errno != 17)
				{
					ft_printf("mkdir: {lred}{bold}error:{reset} %s\n",
						strerror(errno));
					quit(env, ERROR);
				}
			}
			**p = '/';
		}
		(*p)++;
	}
}

void		mkdir_p(t_asm *env, char *dir)
{
	char	*p;
	size_t	len;

	len = ft_strlen(dir);
	if (dir[len - 1] == '/')
		dir[len - 1] = '\0';
	p = dir + 1;
	mkwhile(env, dir, &p);
	if (mkdir(dir, 0777))
	{
		if (errno != 17)
		{
			ft_printf("mkdir: {lred}{bold}error:{reset} %s\n",
				strerror(errno));
			quit(env, ERROR);
		}
	}
}
