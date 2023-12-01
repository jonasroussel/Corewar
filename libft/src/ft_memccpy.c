/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 20:37:03 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/28 14:20:59 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, const t_byte byte,
						const size_t size)
{
	size_t	i;

	i = 0;
	while (i++ < size)
	{
		*(t_byte *)dest++ = *(t_byte *)src;
		if (*(t_byte *)src++ == byte)
			return ((t_byte *)dest);
	}
	return (NULL);
}
