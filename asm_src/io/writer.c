/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 14:20:56 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/28 14:19:25 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	write_data(int fd, t_nbr data, short size)
{
	short	i;

	i = size;
	while (--i > -1)
		write(fd, data.mem + i, 1);
}

void	write_header(t_prog *prog, int fd)
{
	t_nbr	tmp;

	tmp.ul = prog->header->magic;
	write_data(fd, tmp, 4);
	write(fd, prog->header->name, sizeof(prog->header->name) - 1);
	tmp.ul = progsize(prog);
	write_data(fd, tmp, 8);
	write(fd, prog->header->comment, sizeof(prog->header->comment) - 1);
	tmp.l = 0;
	write(fd, &tmp.l, 4);
}

void	write_base(t_code *code, int fd)
{
	t_nbr			tmp;
	t_op			op;
	t_byte			ocp;

	op = g_op_tab[code->index];
	tmp.ul = op.opcode;
	write(fd, &tmp.ul, 1);
	if (op.ocp)
	{
		ocp = codetype(code->argt[0]) << 6;
		ocp |= codetype(code->argt[1]) << 4;
		ocp |= codetype(code->argt[2]) << 2;
		write(fd, &ocp, 1);
	}
}

void	write_params(t_code *code, int fd)
{
	t_op			op;
	unsigned char	i;

	op = g_op_tab[code->index];
	i = 0;
	while (i < op.nb_arg)
	{
		if (code->argt[i] == T_REG)
			write_data(fd, code->args[i], T_REG_SIZE);
		else if (code->argt[i] == T_IND || (code->argt[i] == T_DIR && op.index))
			write_data(fd, code->args[i], T_IND_SIZE);
		else if (code->argt[i] == T_DIR)
			write_data(fd, code->args[i], T_DIR_SIZE);
		i++;
	}
}
