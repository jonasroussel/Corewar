/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_unicode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 17:25:43 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/28 14:21:42 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	pf_write_unicode(t_pf_vars *vars, wchar_t wc, int size, int *i)
{
	if (size == 1)
		vars->output[(*i)++] = (t_byte)wc;
	else if (size == 2)
	{
		vars->output[(*i)++] = ((wc & 0x7C0) >> 6) | 0xC0;
		vars->output[(*i)++] = (wc & 0x3F) | 0x80;
	}
	else if (size == 3)
	{
		vars->output[(*i)++] = ((wc & 0xF000) >> 12) | 0xE0;
		vars->output[(*i)++] = ((wc & 0xFC0) >> 6) | 0x80;
		vars->output[(*i)++] = (wc & 0x3F) | 0x80;
	}
	else
	{
		vars->output[(*i)++] = ((wc & 0x1C0000) >> 18) | 0xF0;
		vars->output[(*i)++] = ((wc & 0x3F000) >> 12) | 0x80;
		vars->output[(*i)++] = ((wc & 0xFC0) >> 6) | 0x80;
		vars->output[(*i)++] = (wc & 0x3F) | 0x80;
	}
}

int		pf_bin_size(wchar_t wc)
{
	int size;

	size = 1;
	if (MB_CUR_MAX == 1 && wc > 127 && wc < 256)
		return (size);
	while (wc /= 2)
		size++;
	if (size <= 7)
		return (1);
	else if (size <= 11)
		return (2);
	else if (size <= 16)
		return (3);
	else
		return (4);
}
