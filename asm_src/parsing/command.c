/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroussel <jroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 11:59:37 by jroussel          #+#    #+#             */
/*   Updated: 2019/02/14 13:56:50 by jroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	start_param(t_prog *prog, unsigned int *i, t_byte type,
	t_parse val)
{
	while (ft_isblank(prog->content[*i]) && prog->content[*i] != '\0')
		(*i)++;
	if (ft_isnl(prog->content[*i]) || is_comment(prog->content[*i])
			|| prog->content[*i] == '\0')
	{
		debug(ERROR, prog, type == CMD_NAME ? NAME_REQ_STR_PARAM
				: COMMENT_REQ_STR_PARAM, ((long)val.s) << 32 | val.j);
		gotonxl(prog->content, i);
		return (SORC);
	}
	else if (prog->content[*i] != '"')
	{
		debug(ERROR, prog, CMD_STRING_PARAM, ((long)(*i + 1)) << 32);
		gotonxl(prog->content, i);
		return (SORC);
	}
	return (0);
}

static int	verif_param(t_prog *prog, unsigned int *i, t_byte type, t_parse val)
{
	if (prog->content[*i + val.len] == '\0')
	{
		debug(ERROR, prog, type == CMD_NAME ? NAME_NVR_CLOSED
			: COMMENT_NVR_CLOSED, ((long)val.s) << 32 | val.j);
		gotonxl(prog->content, i);
		return (SORC);
	}
	(*i) += val.len + 1;
	while (ft_isblank(prog->content[*i]) && prog->content[*i] != '\0')
		(*i)++;
	if (!ft_isnl(prog->content[*i]) && prog->content[*i] != '\0'
			&& !is_comment(prog->content[*i]))
	{
		debug(ERROR, prog, type == CMD_NAME ? NAME_REMAINS_CONTENT
			: CONTENT_EOC, ((long)*i) << 32);
		gotonxl(prog->content, i);
		return (SORC);
	}
	return (0);
}

static int	parse_param(t_prog *prog, unsigned int *i, unsigned int j,
	t_byte type)
{
	t_parse	val;

	val.s = *i;
	*i += (val.j = j);
	if ((val.ret = start_param(prog, i, type, val)))
		return (val.ret);
	val.len = 0;
	while ((++val.len) && prog->content[*i + val.len] != '"'
		&& prog->content[*i + val.len] != '\0')
	{
		if (val.len > (type == CMD_NAME ? PROG_NAME_LENGTH : COMMENT_LENGTH))
		{
			debug(ERROR, prog, type == CMD_NAME ? NAME_TOO_LONG
				: COMMENT_TOO_LONG, ((long)val.s) << 32 | val.j);
			gotonxl(prog->content, i);
			return (SORC);
		}
		if (type == CMD_NAME)
			prog->header->name[val.len - 1] = prog->content[*i + val.len];
		else
			prog->header->comment[val.len - 1] = prog->content[*i + val.len];
	}
	if ((val.ret = verif_param(prog, i, type, val)))
		return (val.ret);
	return (0);
}

static int	parse_cmd(t_asm *env, t_prog *prog, unsigned int *i, unsigned int j)
{
	int	ret;

	if (j == 0)
	{
		debug(ERROR, prog, CMD_EMPTY, ((long)*i) << 32);
		gotonxl(prog->content, i);
		return (SORC);
	}
	else if (ft_strncmp(prog->content + (*i), NAME_CMD_STRING,
		sizeof(NAME_CMD_STRING) - 1) == 0)
	{
		if ((ret = parse_param(prog, i, j, CMD_NAME)))
			return (ret);
		return (!(prog->named = TRUE));
	}
	else if (ft_strncmp(prog->content + (*i), COMMENT_CMD_STRING,
			sizeof(COMMENT_CMD_STRING) - 1) == 0)
		return (parse_param(prog, i, j, CMD_COMMENT));
	debug(env->flags & FLAG_WERROR ? ERROR : WARNING, prog, CMD_UNKNOW,
		((long)*i) << 32 | (j - 1));
	gotonxl(prog->content, i);
	return (SORC);
}

int			next_cmd(t_asm *env, t_prog *prog, unsigned int *i)
{
	unsigned short	j;
	int				ret;

	if ((ret = search_start(prog, i)) > -1)
		return (ret);
	if (prog->content[*i] != CMD_CHAR)
		return (0);
	(*i)++;
	j = 0;
	while (isoneof(prog->content[*i + j], LABEL_CHARS)
			|| prog->content[*i + j] == '-')
		j++;
	if (ft_isdigit(prog->content[*i]))
	{
		debug(ERROR, prog, CMD_START_NUMBER, ((long)*i) << 32 | j);
		gotonxl(prog->content, i);
		return (SORC);
	}
	if ((ret = parse_cmd(env, prog, i, j)))
		return (ret);
	return (1);
}
