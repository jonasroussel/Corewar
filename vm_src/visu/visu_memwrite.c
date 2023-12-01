/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_memwrite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 11:02:17 by tboissel          #+#    #+#             */
/*   Updated: 2019/02/02 16:06:51 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	reverse_opcode(t_proc *proc, t_vm *vm, t_byte rev)
{
	int	start;

	if (vm->mem[proc->pc] - 1 != proc->action)
		return ;
	start = proc->pc % MEM_SIZE + 1;
	wattron(vm->visu->memory, COLOR_PAIR(proc->pnum + 1));
	wmove(vm->visu->memory, 1 + (MEM_SIZE - start) / vm->visu->per_line,
		vm->visu->left + 3 * ((MEM_SIZE - start) % vm->visu->per_line));
	rev ? wattron(vm->visu->memory, A_REVERSE) : 0;
	wprintw(vm->visu->memory, "%.2x", vm->mem[proc->pc]);
	rev ? wattroff(vm->visu->memory, A_REVERSE) : 0;
	wrefresh(vm->visu->memory);
}

void	write_mem(t_vm *vm, t_proc *proc, unsigned int pc, t_byte *val)
{
	int		i;
	t_coord point;

	wattron(vm->visu->memory, COLOR_PAIR(proc->pnum + 1));
	i = REG_SIZE;
	point.y = 1 + (MEM_SIZE - pc) / vm->visu->per_line;
	point.x = vm->visu->left + 3 * ((MEM_SIZE - pc) % vm->visu->per_line);
	wmove(vm->visu->memory, point.y, point.x);
	while (i-- && (point.x += 3))
	{
		if (point.x >= COLS - (COLS > 210 ? 51 : 0))
			wmove(vm->visu->memory, ++point.y, (point.x = vm->visu->left));
		wprintw(vm->visu->memory, "%.2x ", val[i]);
		if (!(pc - REG_SIZE + i) && (point.y = 1))
			wmove(vm->visu->memory, point.y, (point.x = vm->visu->left));
	}
	wrefresh(vm->visu->memory);
	wattroff(vm->visu->memory, COLOR_PAIR(proc->pnum + 1));
}

void	write_all_memory(t_vm *vm, t_visu *visu)
{
	long	size_cur;
	int		i;
	int		player_nb;
	int		pc;
	t_coord	point;

	player_nb = 0;
	size_cur = 0;
	move(LINES - 1, COLS - 1);
	i = MEM_SIZE;
	point.y = 0;
	point.x = 0;
	while (i--)
	{
		if (!size_cur--)
			pc = MEM_SIZE - 1 - (player_nb * MEM_SIZE / vm->pct);
		if (!size_cur)
			wattroff(visu->memory, COLOR_PAIR(player_nb));
		if (i == pc && (size_cur = vm->sizes[player_nb++]))
			wattron(visu->memory, COLOR_PAIR(player_nb));
		if (!point.x-- && ++point.y && (point.x = visu->per_line - 1))
			wmove(visu->memory, point.y, visu->left);
		wprintw(visu->memory, "%.2x ", vm->mem[i]);
	}
	wrefresh(visu->memory);
}
