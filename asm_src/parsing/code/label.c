/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 11:59:35 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/28 14:19:25 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	check_base(t_asm *env, t_prog *prog, t_vars *vars)
{
	unsigned int	k;

	if (vars->wait_code)
	{
		vars->wait_code = FALSE;
		add_code(env, prog, vars->code);
		if (!(vars->code = (t_code *)ft_memalloc(sizeof(t_code))))
			quit(env, MALLOC_ERROR);
		vars->code->start = vars->start;
	}
	k = 0;
	while (k < vars->j)
	{
		if (!isoneof(prog->content[vars->i + k], LABEL_CHARS))
		{
			debug(ERROR, prog, BAD_CHAR_LABEL, ((long)vars->i) << 32 | vars->j);
			gotonxl(prog->content, &vars->i);
			return (SORC);
		}
		k++;
	}
	return (0);
}

static int	check_empty(t_asm *env, t_prog *prog, t_vars *vars)
{
	if (vars->j == 0)
	{
		debug(ERROR, prog, LABEL_EMPTY, ((long)vars->i) << 32);
		gotonxl(prog->content, &vars->i);
		return (SORC);
	}
	if (!(vars->code->label = ft_strsub(prog->content, vars->i, vars->j)))
	{
		ft_memdel((void **)vars->code);
		quit(env, MALLOC_ERROR);
	}
	return (0);
}

static int	check_errors(t_prog *prog, t_vars *vars)
{
	vars->i += vars->j + 1;
	while (ft_isblank(prog->content[vars->i]) && prog->content[vars->i] != '\0')
		vars->i++;
	if (prog->content[vars->i] == '\0')
		return (0);
	if (ft_isnl(prog->content[vars->i]))
	{
		vars->wait_code = TRUE;
		vars->i++;
		return (1);
	}
	if (is_comment(prog->content[vars->i]))
	{
		vars->wait_code = TRUE;
		gotonxl(prog->content, &vars->i);
		return (1);
	}
	return (-1);
}

int			parse_label(t_asm *env, t_prog *prog, t_vars *vars)
{
	int		ret;
	t_list	*iter;

	if (prog->content[vars->i + vars->j] == LABEL_CHAR)
	{
		if ((ret = check_base(env, prog, vars)))
			return (ret);
		if ((ret = check_empty(env, prog, vars)))
			return (ret);
		iter = prog->codes;
		while (iter != NULL)
		{
			if (ft_equal(((t_code *)iter->content)->label, vars->code->label))
			{
				debug(ERROR, prog, LABEL_EXIST, ((long)vars->i) << 32
					| vars->j);
				gotonxl(prog->content, &vars->i);
				return (SORC);
			}
			iter = iter->next;
		}
		if ((ret = check_errors(prog, vars)) > -1)
			return (ret);
	}
	return (2);
}
