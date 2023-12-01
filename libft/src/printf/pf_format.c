/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 15:47:09 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/28 14:21:42 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static int	putprefix(t_pf_vars *vars, int i)
{
	int j;

	j = 0;
	while (j < vars->prlen)
		vars->output[i++] = vars->prefix[j++];
	return (i);
}

static int	putprecision(t_pf_vars *vars, int i)
{
	int j;

	j = -1;
	while (++j < vars->precision)
		vars->output[i++] = '0';
	return (i);
}

static int	putvalue(t_pf_vars *vars, int i)
{
	int j;

	j = 0;
	while (j < vars->valen)
		vars->output[i++] = vars->value[j++];
	return (i);
}

static int	putwidth(t_pf_vars *vars, char c, int i)
{
	int j;

	j = -1;
	while (++j < vars->width)
		vars->output[i++] = c;
	return (i);
}

void		pf_format(t_pf_vars *vars)
{
	if (vars->options['-'])
		putwidth(vars, ' ', putvalue(vars, putprecision(vars,
			putprefix(vars, 0))));
	else
	{
		if (vars->precision == -1)
		{
			if (vars->options['0'])
				putvalue(vars, putwidth(vars, '0', putprefix(vars, 0)));
			else
				putvalue(vars, putprefix(vars, putwidth(vars, ' ', 0)));
		}
		else
			putvalue(vars, putprecision(vars, putprefix(vars,
				putwidth(vars, ' ', 0))));
	}
}
