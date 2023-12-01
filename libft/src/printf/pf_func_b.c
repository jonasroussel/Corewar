/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_func_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 14:57:52 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/28 14:21:42 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	pf_func_b(t_pf_vars *vars, va_list *args)
{
	t_bool	val;

	val = (t_bool)va_arg(*args, long);
	vars->olen = 5 - !!val;
	pf_create_output(vars);
	if (val)
	{
		vars->output[0] = 't';
		vars->output[1] = 'r';
		vars->output[2] = 'u';
		vars->output[3] = 'e';
	}
	else
	{
		vars->output[0] = 'f';
		vars->output[1] = 'a';
		vars->output[2] = 'l';
		vars->output[3] = 's';
		vars->output[4] = 'e';
	}
	pf_write_output(vars);
}
