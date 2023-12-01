/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 11:03:15 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/28 14:20:59 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *search, const size_t size)
{
	size_t	len;
	size_t	i;
	size_t	j;

	len = ft_strlen(search);
	if (len == 0)
		return ((char *)str);
	i = 0;
	while (str[i] != '\0' && i < size)
	{
		j = 0;
		while (search[j] == str[i + j] && i + j < size)
		{
			if (j == len - 1)
				return ((char *)(str + i));
			j++;
		}
		i++;
	}
	return (NULL);
}
