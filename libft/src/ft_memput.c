/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memput.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 19:49:33 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/28 14:20:59 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memput(void *mem, const intmax_t data, const uint8_t size,
					const size_t amount)
{
	size_t	i;
	uint8_t	j;

	i = 0;
	while (i < amount * size)
	{
		j = -1;
		while (++j < size)
			((t_byte *)mem)[i + j] = (data >> (j * 8)) & 0xff;
		i += size;
	}
	return (mem);
}
