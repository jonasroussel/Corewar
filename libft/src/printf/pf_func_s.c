/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_func_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 15:49:24 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/28 14:21:42 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static void	fill_right(t_pf_vars *vars, char *str)
{
	int i;

	i = 0;
	while (i < vars->olen)
	{
		vars->output[i] = str[i];
		i++;
	}
	i = 0;
	while (i < vars->width)
		vars->output[i++ + vars->olen] = ' ';
}

static void	fill_left(t_pf_vars *vars, char *str)
{
	int i;

	i = 0;
	while (i < vars->width)
		vars->output[i++] = vars->options['0'] ? '0' : ' ';
	i = 0;
	while (i < vars->olen)
	{
		vars->output[i + vars->width] = str[i];
		i++;
	}
}

void		pf_func_s(t_pf_vars *vars, va_list *args)
{
	char	*str;

	str = NULL;
	if (vars->size == 'l')
	{
		pf_func_ss(vars, args);
		return ;
	}
	str = va_arg(*args, char *);
	if (str == NULL)
		str = "(null)";
	vars->olen = ft_strlen(str);
	if (vars->precision > -1 && vars->olen > vars->precision)
		vars->olen = vars->precision;
	pf_create_output(vars);
	if (vars->options['-'])
		fill_right(vars, str);
	else
		fill_left(vars, str);
	pf_write_output(vars);
}
