/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_func_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 16:09:03 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/28 14:21:42 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static intmax_t	get_nbr(t_pf_vars *vars, va_list *args)
{
	if (vars->size == 0)
		return (va_arg(*args, int));
	else if (vars->size == 'h')
		return ((short)va_arg(*args, int));
	else if (vars->size == 'H')
		return ((char)va_arg(*args, int));
	else if (vars->size == 'l')
		return (va_arg(*args, long));
	else if (vars->size == 'L')
		return (va_arg(*args, long long));
	else if (vars->size == 'j')
		return (va_arg(*args, intmax_t));
	else if (vars->size == 'z')
		return (va_arg(*args, size_t));
	return (va_arg(*args, int));
}

static void		remove_negative(t_pf_vars *vars)
{
	char	*tmp;
	int		i;

	if (!(tmp = ft_strnew(vars->valen - 1)))
		exit(-1);
	i = -1;
	while (++i < vars->valen - 1)
		tmp[i] = vars->value[i + 1];
	free(vars->value);
	vars->value = tmp;
	vars->valen--;
}

static void		set_value(uintmax_t nbr, t_pf_vars *vars)
{
	if (nbr == 0 && vars->precision == 0)
	{
		if (!(vars->value = ft_strdup("")))
			exit(-1);
	}
	else if (!(vars->value = ft_ltoa(nbr)))
		exit(-1);
}

void			pf_func_d(t_pf_vars *vars, va_list *args)
{
	intmax_t	nbr;

	nbr = get_nbr(vars, args);
	set_value(nbr, vars);
	vars->valen = ft_strlen(vars->value);
	vars->negative = vars->value[0] == '-';
	if (vars->negative)
		remove_negative(vars);
	pf_define_prefix(vars);
	if (vars->precision != -1 && (vars->precision =
			vars->precision - vars->valen) < 0)
		vars->precision = 0;
	vars->olen = vars->prlen + (vars->precision == -1 ? 0 : vars->precision)
		+ vars->valen;
	pf_create_output(vars);
	pf_format(vars);
	if (vars->prlen > 0)
		free(vars->prefix);
	free(vars->value);
	pf_write_output(vars);
}
