/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_func_ss.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 18:07:22 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/28 14:21:42 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static void		fill_right(t_pf_vars *vars, wchar_t *wstr)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while (i < vars->olen)
	{
		if (MB_CUR_MAX == 1 && wstr[j] > 127 && wstr[j] < 256)
			vars->output[i++] = (char)wstr[j];
		else
			pf_write_unicode(vars, wstr[j], pf_bin_size(wstr[j]), &i);
		j++;
	}
	i = 0;
	while (i < vars->width)
		vars->output[i++ + vars->olen] = ' ';
}

static void		fill_left(t_pf_vars *vars, wchar_t *wstr)
{
	int i;
	int	j;

	i = 0;
	while (i < vars->width)
		vars->output[i++] = vars->options['0'] ? '0' : ' ';
	i = vars->width;
	j = 0;
	while (i < vars->olen + vars->width)
	{
		if (MB_CUR_MAX == 1 && wstr[j] > 127 && wstr[j] < 256)
			vars->output[i++] = (char)wstr[j];
		else
			pf_write_unicode(vars, wstr[j], pf_bin_size(wstr[j]), &i);
		j++;
	}
}

static size_t	pf_wstrlen(wchar_t *wstr, t_pf_vars *vars)
{
	size_t	len;
	int		i;

	len = 0;
	i = 0;
	while (wstr[i] != '\0')
	{
		if (wstr[i] < 0 || wstr[i] > 0x10FFFF)
			return (-1);
		else if (MB_CUR_MAX == 1 && wstr[i] > 255)
		{
			vars->len = -1;
			return (-1);
		}
		len += pf_bin_size(wstr[i++]);
	}
	return (len);
}

static int		get_plen(t_pf_vars *vars, wchar_t *wstr)
{
	int	len;
	int	i;

	if (vars->precision != -1)
	{
		len = 0;
		i = 0;
		while (wstr[i] != '\0')
		{
			if (wstr[i] < 0 || wstr[i] > 0x10FFFF)
				return (-1);
			else if (MB_CUR_MAX == 1 && wstr[i] > 255)
			{
				vars->len = -1;
				return (-1);
			}
			if (len + pf_bin_size(wstr[i]) > vars->precision)
				break ;
			len += pf_bin_size(wstr[i++]);
		}
	}
	else
		return (pf_wstrlen(wstr, vars));
	return (len);
}

void			pf_func_ss(t_pf_vars *vars, va_list *args)
{
	wchar_t	*wstr;

	wstr = va_arg(*args, wchar_t *);
	if (wstr == NULL)
		wstr = L"(null)";
	if ((vars->olen = get_plen(vars, wstr)) == -1)
		return ;
	pf_create_output(vars);
	if (vars->options['-'])
		fill_right(vars, wstr);
	else
		fill_left(vars, wstr);
	pf_write_output(vars);
}
