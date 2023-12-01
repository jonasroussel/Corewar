/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 20:49:58 by twalpert          #+#    #+#             */
/*   Updated: 2019/01/26 20:51:41 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	add(t_vm *vm, t_proc *proc)
{
	t_reg	augend;
	t_reg	addend;
	t_reg	summand;
	int		rem;
	int		i;

	(void)vm;
	augend = proc->reg[proc->args[0].u];
	addend = proc->reg[proc->args[1].u];
	proc->carry = 1;
	rem = 0;
	i = -1;
	while (++i < REG_SIZE)
	{
		if ((summand.r[i] = augend.r[i] + addend.r[i] + rem))
			proc->carry = 0;
		rem = (augend.r[i] + addend.r[i] + rem) > 0xff;
	}
	proc->reg[proc->args[2].u] = summand;
}

void	sub(t_vm *vm, t_proc *proc)
{
	t_reg	minuend;
	t_reg	subtrahend;
	t_reg	difference;
	int		rem;
	int		i;

	(void)vm;
	minuend = proc->reg[proc->args[0].u];
	subtrahend = proc->reg[proc->args[1].u];
	proc->carry = 1;
	rem = 0;
	i = -1;
	while (++i < REG_SIZE)
	{
		if ((difference.r[i] = minuend.r[i] - subtrahend.r[i] - rem))
			proc->carry = 0;
		rem = (minuend.r[i] - subtrahend.r[i] - rem) < 0;
	}
	proc->reg[proc->args[2].u] = difference;
}

void	and(t_vm *vm, t_proc *proc)
{
	t_reg	res;
	int		i;

	i = 2;
	while (i--)
		if (((proc->arcode >> (6 - i * 2)) & 0b11) == IND_CODE)
		{
			vm_indmod(proc, &proc->args[i], IDX_MOD);
			proc->args[i] = vm_getmem(vm, DIR_SIZE, &proc->args[i].u);
		}
	proc->carry = 1;
	i = -1;
	while (++i < REG_SIZE)
		if ((res.r[i] = proc->args[0].r[i] & proc->args[1].r[i]))
			proc->carry = 0;
	proc->reg[proc->args[2].u] = res;
}

void	or(t_vm *vm, t_proc *proc)
{
	t_reg	res;
	int		i;

	i = 2;
	while (i--)
		if (((proc->arcode >> (6 - i * 2)) & 0b11) == IND_CODE)
		{
			vm_indmod(proc, &proc->args[i], IDX_MOD);
			proc->args[i] = vm_getmem(vm, DIR_SIZE, &proc->args[i].u);
		}
	proc->carry = 1;
	while (++i < REG_SIZE)
		if ((res.r[i] = proc->args[0].r[i] | proc->args[1].r[i]))
			proc->carry = 0;
	proc->reg[proc->args[2].u] = res;
}

void	xor(t_vm *vm, t_proc *proc)
{
	t_reg	res;
	int		i;

	i = 2;
	while (i--)
		if (((proc->arcode >> (6 - i * 2)) & 0b11) == IND_CODE)
		{
			vm_indmod(proc, &proc->args[i], IDX_MOD);
			proc->args[i] = vm_getmem(vm, DIR_SIZE, &proc->args[i].u);
		}
	proc->carry = 1;
	i = -1;
	while (++i < REG_SIZE)
		if ((res.r[i] = proc->args[0].r[i] ^ proc->args[1].r[i]))
			proc->carry = 0;
	proc->reg[proc->args[2].u] = res;
}
