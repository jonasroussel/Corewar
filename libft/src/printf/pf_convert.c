/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 14:28:46 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/28 14:21:42 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static t_pf_func	g_funcs[] = {
	{ &pf_func_percent, '%' },
	{ &pf_func_s, 's' },
	{ &pf_func_ss, 'S' },
	{ &pf_func_p, 'p' },
	{ &pf_func_d, 'd' },
	{ &pf_func_dd, 'D' },
	{ &pf_func_i, 'i' },
	{ &pf_func_o, 'o' },
	{ &pf_func_oo, 'O' },
	{ &pf_func_u, 'u' },
	{ &pf_func_uu, 'U' },
	{ &pf_func_x, 'x' },
	{ &pf_func_xx, 'X' },
	{ &pf_func_c, 'c' },
	{ &pf_func_cc, 'C' },
	{ &pf_func_n, 'n' },
	{ &pf_func_w, 'w' },
	{ &pf_func_b, 'b' }
};

void	pf_convert(t_pf_vars *vars, va_list *args)
{
	int i;

	i = 0;
	while (i < (int)sizeof(g_funcs))
	{
		if (g_funcs[i].flag == vars->flag)
		{
			g_funcs[i].call(vars, args);
			break ;
		}
		i++;
	}
}
