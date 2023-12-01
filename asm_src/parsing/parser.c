/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroussel <jroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 11:59:43 by jroussel          #+#    #+#             */
/*   Updated: 2019/02/14 13:48:22 by jroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_bool	check_name(t_asm *env, t_prog *prog)
{
	if (!prog->named)
	{
		ft_printf("%s: {lred}{bold}error:{reset} %s\n", prog->file, NAME_UNSET);
		prog->wrong = TRUE;
		if (SORC == STOP || env->flags & FLAG_QUIT)
			return (end(FALSE, prog));
	}
	return (TRUE);
}

static void		check_last(t_asm *env, t_prog *prog, t_code *last)
{
	t_list	*iter;

	if (last == NULL)
		return ;
	iter = prog->codes;
	if (iter == NULL)
		return ;
	while (iter->next != NULL)
		iter = iter->next;
	if (iter->content != last)
		add_code(env, prog, last);
}

static t_bool	commands(t_asm *env, t_prog *prog, unsigned int *i)
{
	int	ret;

	while ((ret = next_cmd(env, prog, i)))
	{
		if (ret < 0 && (prog->wrong = TRUE)
				&& (ret == STOP || env->flags & FLAG_QUIT))
			return (end(FALSE, prog));
	}
	if (!check_name(env, prog))
		return (FALSE);
	return (TRUE);
}

static t_bool	check_ret(t_asm *env, t_prog *prog, t_vars *vars, int ret)
{
	if (ret < 0 && !vars->wait_code)
	{
		prog->wrong = TRUE;
		if (vars->code->label != NULL)
			add_code(env, prog, vars->code);
		else
			free_code(&vars->code);
	}
	if (ret < 0 && (ret == STOP || env->flags & FLAG_QUIT))
	{
		if (vars->wait_code)
			free_code(&vars->code);
		prog->wrong = TRUE;
		return (end(FALSE, prog));
	}
	return (TRUE);
}

t_bool			parser(t_asm *env, t_prog *prog)
{
	int		ret;
	t_vars	vars;

	ft_bzero(&vars, sizeof(t_vars));
	if (!(ret = commands(env, prog, &vars.i)))
		return (ret);
	if (prog->content[vars.i] == '\0')
		return (TRUE);
	while ((ret = next_code(env, prog, &vars)))
	{
		if (!check_ret(env, prog, &vars, ret))
			return (FALSE);
	}
	check_last(env, prog, vars.code);
	if (!check_labels(prog))
		return (end(FALSE, prog));
	return (end(TRUE, prog));
}
