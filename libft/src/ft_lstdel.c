/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 13:14:20 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/28 14:20:59 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **plist, t_bool force)
{
	t_list	*iter;
	t_list	*next;

	if (plist == NULL)
		return ;
	iter = *plist;
	while (iter)
	{
		next = iter->next;
		if (iter->size > 0 || force)
			free(iter->content);
		free(iter);
		iter = next;
	}
	*plist = NULL;
}
