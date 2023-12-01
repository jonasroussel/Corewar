/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 12:03:53 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/28 14:19:25 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_bool		isoneof(char c, const char *chars)
{
	int	i;

	i = ft_strlen(chars);
	while (i--)
		if (c == chars[i])
			return (TRUE);
	return (FALSE);
}

t_bool		is_comment(char c)
{
	size_t	i;

	i = 0;
	while (i < sizeof(COMMENT_CHARS))
	{
		if (c == COMMENT_CHARS[i])
			return (TRUE);
		i++;
	}
	return (FALSE);
}

void		gotonxl(char *content, unsigned int *i)
{
	while (!ft_isnl(content[*i]) && content[*i] != '\0')
		(*i)++;
	if (content[*i] != '\0')
		(*i)++;
}

int			search_start(t_prog *prog, unsigned int *i)
{
	while (ft_isblank(prog->content[*i]) && prog->content[*i] != '\0')
		(*i)++;
	if (prog->content[*i] == '\0')
		return (0);
	if (ft_isnl(prog->content[*i]))
		return (!!++(*i));
	if (is_comment(prog->content[*i]))
	{
		while (!ft_isnl(prog->content[*i]) && prog->content[*i] != '\0')
			(*i)++;
		if (prog->content[*i] == '\0')
			return (0);
		return (!!++(*i));
	}
	return (-1);
}

void		add_code(t_asm *env, t_prog *prog, t_code *code)
{
	t_list	*node;

	if (!(node = ft_lstnew(code, 0)))
		quit(env, MALLOC_ERROR);
	ft_lstpush(&prog->codes, node);
}
