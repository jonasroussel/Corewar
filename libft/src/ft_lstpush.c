/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 16:59:19 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/28 14:20:59 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpush(t_list **plist, t_list *new)
{
	t_list	*iter;

	if (plist == NULL || new == NULL)
		return ;
	iter = *plist;
	if (iter != NULL)
	{
		while (iter->next != NULL)
			iter = iter->next;
		iter->next = new;
	}
	else
		*plist = new;
}
