/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 12:40:11 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/28 14:20:59 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ltoa(intmax_t nbr)
{
	char		*result;
	int			size;
	t_bool		neg;
	intmax_t	lnbr;

	size = 1;
	if ((neg = (nbr < 0)))
	{
		nbr = -nbr;
		size++;
	}
	lnbr = nbr;
	while (nbr /= 10)
		size++;
	if (!(result = ft_strnew(size + 1)))
		return (NULL);
	while (size-- - neg)
	{
		result[size] = lnbr % 10 + '0';
		lnbr /= 10;
	}
	if (neg)
		result[0] = '-';
	return (result);
}
