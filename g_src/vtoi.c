/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 19:16:34 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/28 14:20:12 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "op.h"

static short	get_index(char c, short base, int *size)
{
	const char		lw_sb[] = "0123456789abcdef";
	const char		up_sb[] = "0123456789ABCDEF";
	int				i;

	i = 0;
	while (c != lw_sb[i] && c != up_sb[i])
	{
		i++;
		if (i >= base)
		{
			*size = VAL_OOB;
			return (-1);
		}
	}
	return (i);
}

static short	init(char *v, t_bool neg, short *base, int *size)
{
	*base = 10;
	if (v[0 + neg] == '0' && v[1 + neg] == 'x')
		*base = 16;
	else if (v[0 + neg] == '0' && v[1 + neg] == 'b')
		*base = 2;
	else if (v[0 + neg] == '0')
		*base = 8;
	if (neg && *base != 10)
		return (*size = NEG_IN_NO_B10);
	return (0);
}

static short	is_max_min(t_bool neg, long *ret, int *size)
{
	if (neg)
		*ret = -(*ret);
	if (*ret < INT32_MIN)
		return ((*size = VAL_OIMIN));
	if (*ret > UINT32_MAX)
		return ((*size = VAL_OIMAX));
	return (0);
}

long			vtoi(char *v, int *size)
{
	long	ret;
	short	base;
	int		i;
	t_bool	neg;

	*size = 0;
	base = 0;
	if (!(neg = FALSE) && v[0] == '-')
		neg = TRUE;
	if (!(ret = 0) && init(v, neg, &base, size))
		return (*size);
	i = (base == 16 || base == 2) ? 2 + neg : (int)neg;
	while (v[i] != '\0' && !ft_isblank(v[i]) && !ft_isnl(v[i])
		&& v[i] != SEPARATOR_CHAR && v[i] != '#' && v[i] != ';')
	{
		if (i > 15)
			return ((*size = neg ? VAL_OIMIN : VAL_OIMAX));
		ret = ret * base + get_index(v[i++], base, size);
		if (*size < 0)
			return (*size);
	}
	if (is_max_min(neg, &ret, size))
		return (*size);
	*size = i;
	return (ret);
}
