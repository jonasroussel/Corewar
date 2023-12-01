/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 10:42:21 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/28 14:20:59 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, const char c)
{
	char *last;

	last = NULL;
	while (*str != '\0')
	{
		if (*str == c)
			last = (char *)str;
		str++;
	}
	if (*str == c)
		return ((char *)str);
	return (last);
}
