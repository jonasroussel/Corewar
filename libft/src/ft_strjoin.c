/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 12:56:01 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/28 14:20:59 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	ss1;
	size_t	ss2;
	char	*newstr;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	ss1 = ft_strlen(s1);
	ss2 = ft_strlen(s2);
	if (!(newstr = ft_strnew((ss1 + ss2 + 1) * sizeof(char))))
		return (NULL);
	ft_memcpy(newstr, s1, ss1);
	ft_memcpy(newstr + ss1, s2, ss2);
	newstr[ss1 + ss2] = '\0';
	return (newstr);
}
