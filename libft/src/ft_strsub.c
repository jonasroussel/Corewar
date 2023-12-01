/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 12:47:30 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/28 14:20:59 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(const char *str, const unsigned int start, const size_t size)
{
	char			*new_str;
	unsigned int	i;
	size_t			len;

	len = size;
	if (str == NULL)
		return (NULL);
	if (len == 0)
		len = ft_strlen(str) - start;
	if (!(new_str = ft_strnew(len)))
		return (NULL);
	i = -1;
	while (++i < len)
		new_str[i] = str[start + i];
	new_str[i] = '\0';
	return (new_str);
}
