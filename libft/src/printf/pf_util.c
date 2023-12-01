/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 13:21:06 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/28 14:21:42 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int		pf_isflag(int type, char c)
{
	static char	*flags[] = { "+-#0 ", "%sSpdDioOuUxXcCnwb", "hlzj" };
	int			i;

	i = 0;
	while (flags[type][i] != '\0')
	{
		if (flags[type][i] == c)
			return (c);
		i++;
	}
	return (0);
}

void	pf_define_prefix(t_pf_vars *vars)
{
	vars->prlen = 1;
	if (vars->negative)
		vars->prefix = ft_strdup("-");
	else if (vars->options['+'])
		vars->prefix = ft_strdup("+");
	else if (vars->options[' '])
		vars->prefix = ft_strdup(" ");
	else
	{
		vars->prefix = NULL;
		vars->prlen = 0;
	}
}
