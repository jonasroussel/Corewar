/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 11:59:32 by jroussel          #+#    #+#             */
/*   Updated: 2019/02/16 11:36:06 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int			check_se(t_asm *env, t_prog *prog, t_vars *vars)
{
	int	ret;

	if ((ret = search_start(prog, &vars->i)) > -1)
	{
		if (ret == 0 && vars->wait_code)
		{
			vars->wait_code = FALSE;
			add_code(env, prog, vars->code);
		}
		return (ret);
	}
	if (prog->content[vars->i] == '\0')
	{
		if (vars->wait_code)
		{
			vars->wait_code = FALSE;
			add_code(env, prog, vars->code);
		}
		return (0);
	}
	return (-1);
}

static unsigned int	find_next_label(t_asm *env, t_prog *prog, t_vars *vars)
{
	unsigned int	j;

	j = 0;
	while (prog->content[vars->i + j] != LABEL_CHAR
		&& prog->content[vars->i + j] && !ft_isnl(prog->content[vars->i + j])
		&& !ft_isblank(prog->content[vars->i + j]))
		j++;
	if (!vars->wait_code)
	{
		if (!(vars->code = (t_code *)ft_memalloc(sizeof(t_code))))
			quit(env, MALLOC_ERROR);
		vars->code->start = vars->start;
	}
	return (j);
}

static int			param_debug(t_prog *prog, t_vars *vars)
{
	if (vars->code->index == -1)
		debug(ERROR, prog, UNKNOW_CODE, ((long)vars->i) << 32 | (vars->j - 1));
	else
	{
		if (g_op_tab[vars->code->index].nb_arg == 1)
			debug(ERROR, prog, REQ_1_PARAM, ((long)vars->i) << 32
				| (vars->j - 1));
		else if (g_op_tab[vars->code->index].nb_arg == 2)
			debug(ERROR, prog, REQ_2_PARAM, ((long)vars->i) << 32
				| (vars->j - 1));
		else
			debug(ERROR, prog, REQ_3_PARAM, ((long)vars->i) << 32
				| (vars->j - 1));
	}
	return (0);
}

static int			goto_param(t_prog *prog, t_vars *vars)
{
	vars->j = 0;
	while (ft_islower(prog->content[vars->i + vars->j]))
		vars->j++;
	vars->code->index = get_opindex(prog->content, vars->i, vars->j);
	if (ft_isnl(prog->content[vars->i + vars->j]))
	{
		param_debug(prog, vars);
		gotonxl(prog->content, &vars->i);
		return (SORC);
	}
	if (prog->content[vars->i + vars->j] == '\0')
		return (param_debug(prog, vars));
	if (vars->code->index == -1)
	{
		debug(ERROR, prog, UNKNOW_CODE, ((long)vars->i) << 32 | (vars->j - 1));
		gotonxl(prog->content, &vars->i);
		return (SORC);
	}
	if (!ft_isblank(prog->content[vars->i + vars->j]))
	{
		debug(ERROR, prog, SPACE_MISSING, ((long)(vars->i + vars->j)) << 32);
		gotonxl(prog->content, &vars->i);
		return (SORC);
	}
	return (1);
}

int					next_code(t_asm *env, t_prog *prog, t_vars *vars)
{
	int				ret;

	if ((ret = check_se(env, prog, vars)) > -1)
		return (ret);
	vars->j = find_next_label(env, prog, vars);
	if ((ret = parse_label(env, prog, vars)) != 2)
		return (ret);
	if ((ret = goto_param(prog, vars)) < 1)
		return (ret);
	vars->i += vars->j;
	while (ft_isblank(prog->content[vars->i]))
		vars->i++;
	vars->index = 0;
	while ((ret = next_param(env, prog, vars)))
		if (ret < 0)
			return (SORC);
	if (vars->wait_code)
		vars->wait_code = FALSE;
	vars->code->size = get_size(vars->code);
	vars->start += vars->code->size;
	add_code(env, prog, vars->code);
	gotonxl(prog->content, &vars->i);
	return (1);
}
