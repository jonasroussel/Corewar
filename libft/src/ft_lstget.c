/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 17:22:56 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/28 14:20:59 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstget(t_list *list, const unsigned int index)
{
	unsigned int	i;
	t_list			*iter;

	if (list == NULL)
		return (NULL);
	i = 0;
	iter = list;
	while (iter != NULL)
	{
		if (i == index)
			return (iter);
		iter = iter->next;
		i++;
	}
	return (NULL);
}
