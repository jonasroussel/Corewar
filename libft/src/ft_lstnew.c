/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 12:33:11 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/28 14:20:59 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(const void *content, const size_t size)
{
	t_list	*node;

	if (!(node = (t_list *)ft_memalloc(sizeof(t_list))))
		return (NULL);
	if (content != NULL)
	{
		if (size > 0)
		{
			if (!(node->content = ft_memalloc(size)))
				return (NULL);
			ft_memcpy(node->content, content, size);
		}
		else
			node->content = (void *)content;
		node->size = size;
	}
	else
	{
		node->content = NULL;
		node->size = 0;
	}
	node->next = NULL;
	return (node);
}
