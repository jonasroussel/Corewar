/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 11:59:40 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/28 14:19:25 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_bool	label_valid(t_prog *prog, char *name)
{
	t_list	*iter;
	t_code	*code;

	iter = prog->codes;
	while (iter != NULL)
	{
		code = (t_code *)iter->content;
		if (code->label && ft_equal(code->label, name))
			return (TRUE);
		iter = iter->next;
	}
	return (FALSE);
}

static int		label_gap(t_prog *prog, t_code *origin, char *name)
{
	t_list	*iter;
	t_code	*code;

	iter = prog->codes;
	while (iter != NULL)
	{
		code = (t_code *)iter->content;
		if (code->label && ft_equal(code->label, name))
			return ((int)(code->start - origin->start));
		iter = iter->next;
	}
	return (0);
}

static int		body(t_prog *prog, t_code *code, int i)
{
	if (!label_valid(prog, code->refs[i]))
	{
		debug(ERROR, prog, LABEL_UNSET, ((long)code->pos[i]) << 32
			| (ft_strlen(code->refs[i]) - 1));
		prog->wrong = TRUE;
		if (SORC == STOP)
			return (FALSE);
	}
	else
		code->args[i].l = label_gap(prog, code, code->refs[i]);
	return (TRUE);
}

int				check_labels(t_prog *prog)
{
	t_list	*iter;
	t_code	*code;
	int		i;

	iter = prog->codes;
	while (iter != NULL)
	{
		code = (t_code *)iter->content;
		i = 0;
		while (i < 3)
		{
			if (code->refs[i] && !body(prog, code, i))
				return (FALSE);
			i++;
		}
		iter = iter->next;
	}
	return (TRUE);
}
