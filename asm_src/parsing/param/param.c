/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 11:59:54 by jroussel          #+#    #+#             */
/*   Updated: 2019/02/16 11:44:30 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		get_codelen(t_prog *prog, t_vars *vars, int i)
{
	int		start;
	int		end;

	while (i-- && !ft_isnl(prog->content[i]))
		;
	vars->j = 0;
	while (ft_isblank(prog->content[++i]))
		vars->j += prog->content[i] == '\t' ? 8 - vars->j % 8 : 1;
	vars->s = i;
	start = vars->j;
	while (isoneof(prog->content[i], LABEL_CHARS))
		vars->j += prog->content[i++] == '\t' ? 8 - vars->j % 8 : 1;
	if (prog->content[i] == LABEL_CHAR && (vars->s = ++i))
	{
		while (ft_isblank(prog->content[vars->s]))
			vars->j += prog->content[vars->s++] == '\t' ? 8 - vars->j % 8 : 1;
		start = vars->j;
	}
	vars->j = start;
	i = vars->s;
	while (prog->content[i] && !ft_isnl(prog->content[i])
		&& !is_comment(prog->content[i])
		&& (ft_isblank(prog->content[i]) || (end = vars->j)))
		vars->j += prog->content[i++] == '\t' ? 8 - vars->j % 8 : 1;
	vars->j = end - start;
}

static int		check_nbargs(t_prog *prog, t_vars *vars)
{
	if (vars->index < g_op_tab[vars->code->index].nb_arg)
	{
		get_codelen(prog, vars, vars->s);
		if (g_op_tab[vars->code->index].nb_arg == 1)
			debug(ERROR, prog, REQ_1_PARAM, ((long)vars->s) << 32
				| (vars->j));
		else if (g_op_tab[vars->code->index].nb_arg == 2)
			debug(ERROR, prog, REQ_2_PARAM, ((long)vars->s) << 32
				| (vars->j));
		else
			debug(ERROR, prog, REQ_3_PARAM, ((long)vars->s) << 32
				| (vars->j));
		prog->wrong = TRUE;
	}
	return (0);
}

static void		ignore_spaces(t_prog *prog, t_vars *vars)
{
	unsigned int		end;

	while (ft_isblank(prog->content[vars->i]))
		vars->i++;
	vars->j = 0;
	while (prog->content[vars->i + vars->j]
		&& !ft_isblank(prog->content[vars->i + vars->j])
		&& prog->content[vars->i + vars->j] != SEPARATOR_CHAR
		&& !ft_isnl(prog->content[vars->i + vars->j]))
		vars->j++;
	vars->k = vars->j--;
	while (prog->content[vars->i + vars->k]
		&& ft_isblank(prog->content[vars->i + vars->k]))
		vars->k++;
	end = vars->k;
	while (prog->content[vars->i + vars->k]
		&& prog->content[vars->i + vars->k] != SEPARATOR_CHAR
		&& !ft_isnl(prog->content[vars->i + vars->k])
		&& !is_comment(prog->content[vars->i + vars->k]))
		vars->k++;
	if (end != vars->k)
		debug(ERROR, prog, PARAM_FORMAT, ((long)(vars->i + end)) << 32);
	prog->content[vars->i + vars->k] == SEPARATOR_CHAR ? vars->k++ : 0;
}

static int		check_unused(t_asm *env, t_prog *prog, t_vars *vars)
{
	vars->j = 0;
	while (!is_comment(prog->content[vars->i + vars->j]) && !ft_isnl(
			prog->content[vars->i + vars->j]) && prog->content[vars->i
			+ vars->j] != '\0')
		vars->j++;
	while (ft_isblank(prog->content[vars->i + vars->j - 1]))
		vars->j--;
	debug(env->flags & FLAG_WERROR ? ERROR : WARNING, prog, UNUSED_PARAM,
		((long)(vars->s - 1)) << 32 | ((vars->i - vars->s) + vars->j));
	vars->index = 0;
	if (env->flags & FLAG_WERROR)
	{
		gotonxl(prog->content, &vars->i);
		return (SORC);
	}
	return (0);
}

int				next_param(t_asm *env, t_prog *prog, t_vars *vars)
{
	vars->op = g_op_tab[vars->code->index];
	vars->s = vars->i;
	if ((!prog->content[vars->i] || is_comment(prog->content[vars->i])
		|| ft_isnl(prog->content[vars->i]))
		&& prog->content[vars->i - 1] != SEPARATOR_CHAR)
		return (check_nbargs(prog, vars));
	ignore_spaces(prog, vars);
	if (vars->index >= vars->op.nb_arg)
		return (check_unused(env, prog, vars));
	if (prog->content[vars->i] == 'r')
		return (parse_reg(prog, vars));
	else if (prog->content[vars->i] == DIRECT_CHAR)
		return (parse_dir(env, prog, vars));
	else if (ft_isdigit(prog->content[vars->i]) || prog->content[vars->i]
			== '-' || prog->content[vars->i] == LABEL_CHAR)
		return (parse_ind(env, prog, vars));
	return (error(prog, ++vars->j ? INVALID_PARAM : PARAM_EMPTY, vars,
		((vars->j ? (long)vars->i : vars->s - 1) << 32) | (vars->j - 1)));
}
