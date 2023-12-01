/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 12:36:59 by twalpert          #+#    #+#             */
/*   Updated: 2019/01/28 17:11:30 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	proc_fork(t_vm *vm, t_proc *proc)
{
	t_proc		*newproc;

	if (!(newproc = malloc(sizeof(t_proc))))
		vm_exit(vm, -2, vm->pct);
	*newproc = *proc;
	newproc->next = vm->proc;
	vm_indmod(newproc, &proc->args[0], IDX_MOD);
	newproc->pc = proc->args[0].u;
	vm->proc = newproc;
	vm->procct++;
	if (vm->visu)
		update_fork(vm);
}

void	lfork(t_vm *vm, t_proc *proc)
{
	t_proc		*newproc;

	if (!(newproc = malloc(sizeof(t_proc))))
		vm_exit(vm, -2, vm->pct);
	*newproc = *proc;
	newproc->next = vm->proc;
	vm_indmod(newproc, &proc->args[0], MEM_SIZE);
	newproc->pc = proc->args[0].u;
	vm->proc = newproc;
	vm->procct++;
	if (vm->visu)
		update_fork(vm);
}
