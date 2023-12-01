/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 13:35:51 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/28 14:20:59 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_words_count(const char *str, const char c)
{
	int count;
	int	i;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c)
			i++;
		while (str[i] != c && str[i] != '\0')
			i++;
		if (!(str[i] == '\0' && str[i - 1] == c))
			count++;
	}
	return (count);
}

static char	*ft_getword(int index, const char *str, const char c)
{
	unsigned int	start;
	size_t			size;
	int				i;
	int				count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c)
			i++;
		if (count == index)
			start = i;
		while (str[i] != c && str[i] != '\0')
			i++;
		if (count == index)
			size = i - start;
		if (!(str[i] == '\0' && str[i - 1] == c))
			count++;
	}
	return (ft_strsub(str, start, size));
}

char		**ft_strsplit(const char *str, const char c)
{
	int		words_count;
	char	**tab;
	int		i;
	char	*word;

	if (str == NULL)
		return (NULL);
	words_count = ft_words_count(str, c);
	if (!(tab = (char **)ft_memalloc((words_count + 1) * sizeof(*tab))))
		return (NULL);
	i = 0;
	while (i < words_count)
	{
		if (!(word = ft_getword(i, str, c)))
			return (NULL);
		tab[i++] = word;
	}
	tab[i] = 0;
	return (tab);
}
