/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 13:22:55 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/28 14:20:59 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *m1, const void *m2, const size_t size)
{
	size_t	i;

	i = 0;
	while (i++ < size)
	{
		if (*(t_byte *)m1 != *(t_byte *)m2)
			return (*(t_byte *)m1 - *(t_byte *)m2);
		m1++;
		m2++;
	}
	return (0);
}
