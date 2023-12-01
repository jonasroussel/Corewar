/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 13:08:00 by twalpert          #+#    #+#             */
/*   Updated: 2019/01/27 13:07:00 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	st(t_vm *vm, t_proc *proc)
{
	if (((proc->arcode >> 4) & 0b11) == IND_CODE)
	{
		vm_indmod(proc, &proc->args[1], IDX_MOD);
		vm_putmem(vm, proc->reg[proc->args[0].u], proc->args[1].u, proc);
	}
	else
		proc->reg[proc->args[1].u] = proc->reg[proc->args[0].u];
}

void	sti(t_vm *vm, t_proc *proc)
{
	t_reg	res;
	int		i;
	int		rem;

	i = 2;
	while (i--)
		if (((proc->arcode >> (4 - i * 2)) & 0b11) == IND_CODE)
		{
			vm_indmod(proc, &proc->args[i + 1], IDX_MOD);
			proc->args[i + 1] = vm_getmem(vm, DIR_SIZE, &proc->args[i + 1].u);
		}
	rem = 0;
	while (++i < REG_SIZE)
	{
		res.r[i] = proc->args[2].r[i] + proc->args[1].r[i] + rem;
		rem = (proc->args[2].r[i] + proc->args[1].r[i] + rem) > 0xff;
	}
	vm_indmod(proc, &res, IDX_MOD);
	vm_putmem(vm, proc->reg[proc->args[0].u], res.u, proc);
}
