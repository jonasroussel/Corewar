/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_output.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 19:48:08 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/28 14:21:42 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	pf_write_output(t_pf_vars *vars)
{
	int i;

	i = 0;
	while (i < vars->olen + vars->width)
		pf_write_buff(vars->output[i++], vars);
}

void	pf_create_output(t_pf_vars *vars)
{
	vars->width = vars->width - vars->olen;
	if (vars->width < 0)
		vars->width = 0;
	if (!(vars->output = (t_byte *)malloc(vars->olen + vars->width)))
		exit(-1);
}
