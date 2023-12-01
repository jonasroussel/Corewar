/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 13:11:15 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/28 14:20:59 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *str)
{
	unsigned int	start;
	size_t			size;
	unsigned int	i;

	if (str == NULL)
		return (NULL);
	i = 0;
	while ((ft_isblank(str[i]) || str[i] == '\n') && str[i] != '\0')
		i++;
	if (str[i] == '\0')
		return (ft_strnew(0));
	start = i;
	i = ft_strlen(str) - 1;
	while ((ft_isblank(str[i]) || str[i] == '\n'))
		i--;
	size = i - start;
	return (ft_strsub(str, start, size + 1));
}
