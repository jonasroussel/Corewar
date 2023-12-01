/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 11:59:49 by jroussel          #+#    #+#             */
/*   Updated: 2019/02/15 14:17:21 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	check_type(t_prog *prog, t_vars *vars)
{
	if ((vars->op.args[vars->index] & T_REG) && (vars->op.args[vars->index]
			& T_DIR))
		debug(ERROR, prog, PARAM_REG_DIR, ((long)vars->i) << 32
			| (vars->j - 1));
	else if (vars->op.args[vars->index] & T_REG)
		debug(ERROR, prog, PARAM_REG, ((long)vars->i) << 32 | (vars->j - 1));
	else if (vars->op.args[vars->index] & T_DIR)
		debug(ERROR, prog, PARAM_DIR, ((long)vars->i) << 32 | (vars->j - 1));
	gotonxl(prog->content, &vars->i);
	vars->index = 0;
	return (SORC);
}

static int	ind_val(t_prog *prog, t_vars *vars)
{
	long	val;
	int		size;

	size = 0;
	val = vtoi(prog->content + vars->i, &size);
	if (size == 0 || size == EMPTY_VAL)
		return (error(prog, PARAM_EMPTY, vars, ((long)vars->i) << 32));
	else if (size == VAL_OOB)
		return (error(prog, PARAM_OOB, vars, ((long)vars->i) << 32
			| (vars->j - 1)));
	else if (size == NEG_IN_NO_B10)
		return (error(prog, PARAM_BASE_ERROR, vars, ((long)vars->i) << 32
			| (vars->j - 1)));
	else if (size == VAL_OIMAX || val > UINT16_MAX)
		return (error(prog, OF_MAX_SHORT, vars, ((long)vars->i) << 32
			| (vars->j - 1)));
	else if (size == VAL_OIMIN || val < INT16_MIN)
		return (error(prog, OF_MIN_SHORT, vars, ((long)vars->i) << 32
			| (vars->j - 1)));
	vars->code->argt[vars->index] = T_IND;
	vars->code->args[vars->index].l = val;
	vars->index++;
	vars->i += vars->k;
	return (1);
}

int			parse_ind(t_asm *env, t_prog *prog, t_vars *vars)
{
	if (!(vars->op.args[vars->index] & T_IND))
		return (check_type(prog, vars));
	if (prog->content[vars->i] == LABEL_CHAR)
	{
		vars->type = T_IND;
		return (label_param(env, prog, vars, 1));
	}
	return (ind_val(prog, vars));
}
