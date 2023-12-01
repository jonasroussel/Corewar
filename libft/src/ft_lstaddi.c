/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 17:47:16 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/28 14:20:59 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddi(t_list **plist, t_list *new, const unsigned int index)
{
	t_list			*iter;
	unsigned int	i;

	if (plist == NULL || new == NULL)
		return ;
	if (index == 0)
	{
		ft_lstadd(plist, new);
		return ;
	}
	iter = *plist;
	i = 0;
	while (iter != NULL)
	{
		if (i + 1 == index)
		{
			new->next = iter->next;
			iter->next = new;
			return ;
		}
		iter = iter->next;
		i++;
	}
}
