/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 22:31:37 by twalpert          #+#    #+#             */
/*   Updated: 2019/01/28 10:36:49 by tboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ld(t_vm *vm, t_proc *proc)
{
	int		i;

	i = REG_SIZE;
	if (proc->arcode >> 6 == IND_CODE)
	{
		vm_indmod(proc, &proc->args[0], IDX_MOD);
		proc->args[0] = vm_getmem(vm, DIR_SIZE, &proc->args[0].u);
	}
	proc->carry = 1;
	while (i--)
		if ((proc->reg[proc->args[1].i].r[i] = proc->args[0].r[i]))
			proc->carry = 0;
}

void	lld(t_vm *vm, t_proc *proc)
{
	int		i;

	i = REG_SIZE;
	if (proc->arcode >> 6 == IND_CODE)
	{
		vm_indmod(proc, &proc->args[0], MEM_SIZE);
		proc->args[0] = vm_getmem(vm, DIR_SIZE, &proc->args[0].u);
	}
	proc->carry = 1;
	while (i--)
		if ((proc->reg[proc->args[1].i].r[i] = proc->args[0].r[i]))
			proc->carry = 0;
}

void	ldi(t_vm *vm, t_proc *proc)
{
	t_reg	res;
	int		i;
	int		rem;

	i = 2;
	while (i--)
		if (((proc->arcode >> (6 - i * 2)) & 0b11) == IND_CODE)
		{
			vm_indmod(proc, &proc->args[i], IDX_MOD);
			proc->args[i] = vm_getmem(vm, DIR_SIZE, &proc->args[i].u);
		}
	rem = 0;
	while (++i < REG_SIZE)
	{
		res.r[i] = proc->args[0].r[i] + proc->args[1].r[i] + rem;
		rem = (proc->args[0].r[i] + proc->args[1].r[i] + rem) > 0xff;
	}
	vm_indmod(proc, &res, IDX_MOD);
	proc->reg[proc->args[2].u] = vm_getmem(vm, REG_SIZE, &res.u);
	proc->carry = 1;
	while (i-- && proc->carry)
		if (proc->reg[proc->args[2].u].r[i])
			proc->carry = 0;
}

void	lldi(t_vm *vm, t_proc *proc)
{
	t_reg	res;
	int		i;
	int		rem;

	i = 2;
	while (i--)
		if (((proc->arcode >> (6 - i * 2)) & 0b11) == IND_CODE)
		{
			vm_indmod(proc, &proc->args[i], MEM_SIZE);
			proc->args[i] = vm_getmem(vm, DIR_SIZE, &proc->args[i].u);
		}
	rem = 0;
	while (++i < REG_SIZE)
	{
		res.r[i] = proc->args[0].r[i] + proc->args[1].r[i] + rem;
		rem = (proc->args[0].r[i] + proc->args[1].r[i] + rem) > 0xff;
	}
	vm_indmod(proc, &res, MEM_SIZE);
	proc->reg[proc->args[2].u] = vm_getmem(vm, REG_SIZE, &res.u);
	proc->carry = 1;
	while (i-- && proc->carry)
		if (proc->reg[proc->args[2].u].r[i])
			proc->carry = 0;
}
