/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 12:53:53 by jroussel          #+#    #+#             */
/*   Updated: 2019/02/12 11:29:30 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_ultoa(uintmax_t nbr)
{
	char		*result;
	int			size;
	uintmax_t	lnbr;

	size = 1;
	lnbr = nbr;
	while (nbr /= 10)
		size++;
	if ((result = ft_strnew(size + 1)))
		while (size--)
		{
			result[size] = lnbr % 10 + '0';
			lnbr /= 10;
		}
	return (result);
}
