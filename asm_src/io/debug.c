/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroussel <jroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 12:01:23 by jroussel          #+#    #+#             */
/*   Updated: 2019/02/01 16:24:38 by jroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		usage(short type, char *name, char *arg)
{
	if (type & USAGE_BASE)
	{
		ft_printf("usage: %s [-o | --output <dir>] [-r | --recursive]\n", name);
		ft_printf("             [-W | --Werror] [-q | --quit] [file ...]\n");
		ft_printf("\noptions:\n");
		ft_printf("  --output <dir> Creates the directory if it doesn't exist");
		ft_printf(" and puts all compiled champions within\n");
		ft_printf("  --recursive    Reproduces the source files tree\n");
		ft_printf("  --Werror       Changes warnings into errors\n ");
		ft_printf(" --quit         Stops the compilation at the first error\n");
		exit(NO_ERROR);
	}
	if (type & USAGE_UNKNOW_FLAG)
		ft_printf("%s: {lred}{bold}error:{reset} %s: '%s'\n", name, arg,
			UNKNOW_ARG);
	if (type & USAGE_NO_INPUT)
		ft_printf("%s: {lred}{bold}error:{reset} %s\n", name, INPUT_FILES);
	if (type & USAGE_NO_OUTPUT)
		ft_printf("%s: {lred}{bold}error:{reset} %s\n", name, OUTPUT_DIR);
}

static int	get_start(t_prog *prog, int index)
{
	char	*line;
	int		start;

	start = index;
	while (prog->content[start] != '\n')
		if (--start < 0)
			break ;
	start++;
	if (!(line = get_line(prog->content, start)))
		quit(NULL, MALLOC_ERROR);
	ft_printf("%s\n", line);
	free(line);
	return (start);
}

void		debug(t_byte type, t_prog *prog, char *err, long sign)
{
	t_loc	loc;
	int		i;
	int		signs[2];

	signs[0] = sign >> 32;
	signs[1] = sign & 0xffffffff;
	loc = get_loc(prog->content, signs[0]);
	ft_printf(type == ERROR ? "{bold}%s:%u:%u: {lred}error:{default} \
%s{reset}\n" : "{bold}%s:%u:%u: {lmagenta}warning:{default} %s{reset}\n",
		prog->file, loc.column, loc.line, err);
	if (type == ERROR)
		prog->wrong = TRUE;
	i = get_start(prog, signs[0]) - 1;
	while (++i < signs[0])
		ft_printf("%c", ft_isblank(prog->content[i]) ? prog->content[i] : ' ');
	ft_printf("{lgreen}^");
	i = -1;
	while (++i < signs[1])
		ft_printf("~");
	ft_printf("{reset}\n");
}

int			error(t_prog *prog, char *msg, t_vars *vars, long sign)
{
	debug(ERROR, prog, msg, sign);
	gotonxl(prog->content, &vars->i);
	vars->index = 0;
	return (SORC);
}
