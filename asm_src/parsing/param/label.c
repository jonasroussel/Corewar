/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 11:59:51 by jroussel          #+#    #+#             */
/*   Updated: 2019/02/15 13:30:41 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	lbl_init(t_prog *prog, t_vars *vars, unsigned short jump)
{
	unsigned int	l;

	l = 0;
	while (prog->content[vars->i + jump + l] != SEPARATOR_CHAR
		&& !ft_isnl(prog->content[vars->i + jump + l])
		&& !ft_isblank(prog->content[vars->i + jump + l])
		&& prog->content[vars->i + jump + l] != '\0')
	{
		if (!isoneof(prog->content[vars->i + jump + l], LABEL_CHARS))
		{
			debug(ERROR, prog, BAD_CHAR_LABEL, ((long)vars->i) << 32 | vars->j);
			gotonxl(prog->content, &vars->i);
			vars->index = 0;
			return (SORC);
		}
		l++;
	}
	if (l != 0)
		return (l);
	debug(ERROR, prog, LABEL_EMPTY, ((long)vars->i) << 32 | 1);
	gotonxl(prog->content, &vars->i);
	vars->index = 0;
	return (SORC);
}

int			label_param(t_asm *env, t_prog *prog, t_vars *vars,
				unsigned short jump)
{
	int	l;

	if ((l = lbl_init(prog, vars, jump)) < 0)
		return (l);
	vars->code->argt[vars->index] = vars->type;
	vars->code->pos[vars->index] = vars->i + jump;
	if (!(vars->code->refs[vars->index] = ft_strsub(prog->content,
			vars->i + jump, l)))
		quit(env, MALLOC_ERROR);
	vars->index++;
	vars->i += vars->k;
	return (1);
}
