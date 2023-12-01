/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 12:00:00 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/28 14:19:25 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_bool		end(t_bool ret, t_prog *prog)
{
	if (prog != NULL && prog->content != NULL)
		ft_memdel((void **)&prog->content);
	return (ret);
}

void		free_code(t_code **code)
{
	if (*code)
	{
		if ((*code)->label)
			free((*code)->label);
		if ((*code)->refs[0])
			free((*code)->refs[0]);
		if ((*code)->refs[1])
			free((*code)->refs[1]);
		if ((*code)->refs[2])
			free((*code)->refs[2]);
		ft_memdel((void **)code);
	}
}

static void	free_codes(t_list *codes)
{
	t_list	*next;
	t_code	*code;

	while (codes)
	{
		next = codes->next;
		code = (t_code *)codes->content;
		free_code(&code);
		free(codes);
		codes = next;
	}
}

static void	free_programs(t_list *programs)
{
	t_list	*next;
	t_prog	*prog;

	while (programs)
	{
		next = programs->next;
		prog = (t_prog *)programs->content;
		if (prog->content)
			free(prog->content);
		if (prog->file)
			free(prog->file);
		if (prog->header)
			free(prog->header);
		free_codes(prog->codes);
		free(prog);
		free(programs);
		programs = next;
	}
}

int			quit(t_asm *env, int status)
{
	if (status == MALLOC_ERROR)
		ft_printf("%s: {lred}{bold}error:{reset} %s\n", env->name,
			MALLOC_FAILED);
	if (env)
	{
		if (env->name)
			free(env->name);
		if (env->programs)
			free_programs(env->programs);
		if (env->output)
			free(env->output);
	}
	exit(status);
	return (status);
}
