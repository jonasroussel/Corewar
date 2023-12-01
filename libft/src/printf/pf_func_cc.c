/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_func_cc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 14:30:48 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/28 14:21:42 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static void	fill(t_pf_vars *vars, wchar_t wc)
{
	int i;

	i = 0;
	if (vars->options['-'])
	{
		if (MB_CUR_MAX == 1 && wc > 127 && wc < 256)
			vars->output[i++] = (char)wc;
		else
			pf_write_unicode(vars, wc, vars->olen, &i);
		while (i < vars->width + vars->olen)
			vars->output[i++] = ' ';
	}
	else
	{
		while (i < vars->width)
			vars->output[i++] = vars->options['0'] ? '0' : ' ';
		if (MB_CUR_MAX == 1 && wc > 127 && wc < 256)
			vars->output[i++] = (char)wc;
		else
			pf_write_unicode(vars, wc, vars->olen, &i);
	}
}

void		pf_func_cc(t_pf_vars *vars, va_list *args)
{
	wchar_t	wc;

	wc = va_arg(*args, wchar_t);
	if (MB_CUR_MAX == 1 && wc > 255)
	{
		vars->len = -1;
		return ;
	}
	if (wc < 0 || wc > 0x10FFFF)
		return ;
	vars->olen = pf_bin_size(wc);
	pf_create_output(vars);
	fill(vars, wc);
	pf_write_output(vars);
}
