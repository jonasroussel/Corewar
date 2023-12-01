/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 14:42:42 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/28 14:19:25 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_loc	get_loc(char *content, unsigned int i)
{
	unsigned int	j;
	t_loc			loc;

	j = 0;
	loc.line = 1;
	loc.column = 0;
	while (j < i)
	{
		j++;
		loc.column++;
		if (content[j - 1] == '\n')
		{
			loc.line++;
			loc.column = 0;
		}
	}
	return (loc);
}

char	*get_line(char *content, unsigned int i)
{
	unsigned int	size;

	size = 0;
	while (content[i + size] != '\n' && content[i + size] != '\0'
			&& !is_comment(content[i + size]))
		size++;
	return (ft_strsub(content, i, size));
}

short	get_opindex(char *content, unsigned int start, unsigned int size)
{
	unsigned long	i;
	size_t			opsize;

	i = 0;
	while (i < (sizeof(g_op_tab) / sizeof(t_op)))
	{
		opsize = ft_strlen(g_op_tab[i].name);
		if (ft_strncmp(g_op_tab[i].name, content + start,
				((opsize > size) ? opsize : size)) == 0)
			return ((short)i);
		i++;
	}
	return (-1);
}

short	get_size(t_code *code)
{
	short	size;
	int		i;
	t_op	op;

	op = g_op_tab[code->index];
	size = 1 + !!op.ocp;
	i = 0;
	while (i < 3)
	{
		if (code->argt[i] == T_REG)
			size += T_REG_SIZE;
		else if (code->argt[i] == T_IND)
			size += T_IND_SIZE;
		else if (code->argt[i] == T_DIR)
			size += op.index ? T_IDX_SIZE : T_DIR_SIZE;
		i++;
	}
	return (size);
}
