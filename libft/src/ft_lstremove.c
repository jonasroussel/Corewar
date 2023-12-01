/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 16:10:40 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/28 14:20:59 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_lstclr(t_list *node)
{
	free(node->content);
	free(node);
}

void		ft_lstremove(t_list **plist, t_list *node)
{
	t_list	*iter;
	t_list	*next;

	if (plist == NULL || node == NULL)
		return ;
	if (node == *plist)
	{
		next = (*plist)->next;
		ft_lstclr(*plist);
		*plist = next;
		return ;
	}
	iter = *plist;
	while (iter->next != NULL)
	{
		if (iter->next == node)
		{
			next = iter->next->next;
			ft_lstclr(iter->next);
			iter->next = next;
			return ;
		}
		iter = iter->next;
	}
}
