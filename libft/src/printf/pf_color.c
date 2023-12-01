/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 15:55:16 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/28 14:21:42 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static t_pf_color	g_colors[] = {
	{ "{reset}", "\e[0m" },
	{ "{bold}", "\e[1m" },
	{ "{faint}", "\e[2m" },
	{ "{italic}", "\e[3m" },
	{ "{underline}", "\e[4m" },
	{ "{black}", "\e[30m" },
	{ "{red}", "\e[31m" },
	{ "{green}", "\e[32m" },
	{ "{yellow}", "\e[33m" },
	{ "{blue}", "\e[34m" },
	{ "{magenta}", "\e[35m" },
	{ "{cyan}", "\e[36m" },
	{ "{lgray}", "\e[37m" },
	{ "{default}", "\e[39m" },
	{ "{gray}", "\e[90m" },
	{ "{lred}", "\e[91m" },
	{ "{lgreen}", "\e[92m" },
	{ "{lyellow}", "\e[93m" },
	{ "{lblue}", "\e[94m" },
	{ "{lmagenta}", "\e[95m" },
	{ "{lcyan}", "\e[96m" },
	{ "{white}", "\e[97m" }
};

static void		get_star(t_pf_vars *vars, va_list *args, int *i)
{
	int		j;
	char	*tmp;
	char	*color;
	int		len;

	tmp = va_arg(*args, char *);
	len = ft_strlen(tmp);
	if (!(color = ft_strnew(len + 2)))
		exit(-1);
	color[0] = '{';
	j = -1;
	while (tmp[++j] != '\0')
		color[j + 1] = tmp[j];
	color[len + 1] = '}';
	color[len + 2] = '\0';
	while (*i < (int)(sizeof(g_colors) / sizeof(t_pf_color)))
	{
		if (!ft_strncmp(color, g_colors[*i].id, ft_strlen(g_colors[*i].id)))
			break ;
		(*i)++;
	}
	if (*i < (int)(sizeof(g_colors) / sizeof(t_pf_color)))
		vars->pf += 3;
	free(color);
}

static void		get_color(const char *format, t_pf_vars *vars, int *i)
{
	while (*i < (int)(sizeof(g_colors) / sizeof(t_pf_color)))
	{
		if (!ft_strncmp(format + vars->pf, g_colors[*i].id,
			ft_strlen(g_colors[*i].id)))
		{
			vars->pf += ft_strlen(g_colors[*i].id);
			break ;
		}
		(*i)++;
	}
}

void			pf_parse_color(const char *format, t_pf_vars *vars,
								va_list *args)
{
	int		i;
	int		j;

	i = 0;
	if (!ft_strncmp(format + vars->pf, "{*}", 3))
		get_star(vars, args, &i);
	else
		get_color(format, vars, &i);
	if (i >= (int)(sizeof(g_colors) / sizeof(t_pf_color)))
	{
		pf_write_buff('{', vars);
		vars->pf++;
	}
	else
	{
		j = 0;
		while (g_colors[i].value[j] != '\0')
			pf_write_buff(g_colors[i].value[j++], vars);
	}
}
