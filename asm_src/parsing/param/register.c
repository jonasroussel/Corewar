/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 11:59:56 by jroussel          #+#    #+#             */
/*   Updated: 2019/02/15 14:16:29 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	check_type(t_prog *prog, t_vars *vars)
{
	if ((vars->op.args[vars->index] & T_DIR) && (vars->op.args[vars->index]
			& T_IND))
		debug(ERROR, prog, PARAM_DIR_IND, ((long)vars->i) << 32
			| (vars->j - 1));
	else if (vars->op.args[vars->index] & T_DIR)
		debug(ERROR, prog, PARAM_DIR, ((long)vars->i) << 32 | (vars->j - 1));
	else if (vars->op.args[vars->index] & T_IND)
		debug(ERROR, prog, PARAM_IND, ((long)vars->i) << 32 | (vars->j - 1));
	gotonxl(prog->content, &vars->i);
	vars->index = 0;
	return (SORC);
}

static int	check_errors(t_prog *prog, t_vars *vars, int size, int reg)
{
	if (size == 0 || size == EMPTY_VAL)
		return (error(prog, EMPTY_REG, vars, ((long)vars->i) << 32));
	else if (size == VAL_OOB)
		return (error(prog, PARAM_OOB, vars, ((long)vars->i) << 32
			| (vars->j - 1)));
	else if (size == NEG_IN_NO_B10)
		return (error(prog, PARAM_BASE_ERROR, vars, ((long)vars->i) << 32
			| (vars->j - 1)));
	else if (size == VAL_OIMAX || reg > INT8_MAX)
		return (error(prog, OF_MAX_CHAR, vars, ((long)vars->i) << 32
			| (vars->j - 1)));
	else if (size == VAL_OIMIN || reg < INT8_MIN)
		return (error(prog, OF_MIN_CHAR, vars, ((long)vars->i) << 32
			| (vars->j - 1)));
	else if (reg < 1 || reg > REG_NUMBER)
		return (error(prog, REG_INV_VAL, vars, ((long)vars->i) << 32
			| (vars->j - 1)));
	else
		return (0);
}

int			parse_reg(t_prog *prog, t_vars *vars)
{
	int	reg;
	int	size;

	size = 0;
	if (!(vars->op.args[vars->index] & T_REG))
		return (check_type(prog, vars));
	vars->code->argt[vars->index] = T_REG;
	reg = vtoi(prog->content + vars->i + 1, &size);
	if (check_errors(prog, vars, size, reg))
		return (SORC);
	vars->code->args[vars->index].ul = (unsigned long)reg;
	vars->index++;
	vars->i += vars->k;
	return (1);
}
