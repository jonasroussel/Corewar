/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infos.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 14:45:40 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/28 14:19:25 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

unsigned long			progsize(t_prog *prog)
{
	t_list	*iter;
	t_code	*code;

	iter = prog->codes;
	if (iter == NULL)
		return (0);
	while (iter->next != NULL)
		iter = iter->next;
	code = (t_code *)iter->content;
	return (code->start + code->size);
}

t_byte					codetype(t_byte type)
{
	if (type == T_REG)
		return (REG_CODE);
	if (type == T_DIR)
		return (DIR_CODE);
	if (type == T_IND)
		return (IND_CODE);
	return (0);
}
