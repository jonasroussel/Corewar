/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 13:52:41 by jroussel          #+#    #+#             */
/*   Updated: 2019/02/11 19:00:37 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_ultoa_base(uintmax_t nbr, const uint8_t base)
{
	const char	symbols[] = "0123456789abcdefghijklmnopqrstuvwxyz";
	char		*result;
	int			size;
	uintmax_t	lnbr;

	if (base < 2 || base > 35)
		return (ft_strdup("-1"));
	size = 1;
	lnbr = nbr;
	while (nbr /= base)
		size++;
	if ((result = ft_strnew(size + 1)))
		while (size--)
		{
			result[size] = symbols[lnbr % base];
			lnbr /= base;
		}
	return (result);
}
