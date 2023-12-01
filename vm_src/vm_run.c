/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 17:09:30 by twalpert          #+#    #+#             */
/*   Updated: 2019/02/02 15:15:54 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	vm_opinit(t_vm *vm, t_proc *proc, t_op op)
{
	int			i;
	t_byte		code;
	t_byte		flag;
	t_byte		size;

	proc->cycle += op.cycle;
	i = -1;
	flag = 0;
	proc->arcode = op.ocp ? vm_getmem(vm, 1, &proc->read).u : DIR_CODE << 6;
	while (++i < op.nb_arg && (code = (proc->arcode >> (6 - i * 2)) & 3))
	{
		if (code == REG_CODE && (op.args[i] & T_REG || (flag = -1)))
			size = 1;
		else if ((code == DIR_CODE && (op.args[i] & T_DIR || (flag = -1)))
		|| (code == IND_CODE && (op.args[i] & T_IND || (flag = -1))))
			size = (code == IND_CODE || op.index) ? IND_SIZE : DIR_SIZE;
		proc->args[i] = vm_getmem(vm, size, &proc->read);
		if (code == REG_CODE && proc->args[i].u - 1 >= REG_NUMBER)
			flag = -1;
		else if (code == REG_CODE && op.args[i] & T_DIR)
			proc->args[i] = proc->reg[proc->args[i].i];
	}
	proc->arcode = !code || flag ? 0 : proc->arcode;
	proc->arcode && vm->visu ? reverse_opcode(proc, vm, 1) : 0;
}

t_proc	*vm_livecheck(t_vm *vm)
{
	t_proc		*proc;
	t_proc		*last;

	proc = vm->proc;
	last = NULL;
	if ((vm->lives > NBR_LIVE || ++vm->checks > MAX_CHECKS) && (vm->checks = 1))
		vm->todie -= vm->todie > CYCLE_DELTA ? CYCLE_DELTA : vm->todie;
	vm->nextcheck = vm->todie;
	vm->lives = 1;
	while (proc)
		if (!proc->live || (proc->live = 0))
		{
			if (last || ((vm->proc = proc->next) && 0))
				last->next = proc->next;
			vm->visu && proc->arcode ? reverse_opcode(proc, vm, 0) : 0;
			free(proc);
			proc = last ? last->next : vm->proc;
			vm->procct--;
		}
		else if ((last = proc))
			proc = proc->next;
	if (vm->visu)
		update_fork(vm);
	return (vm->proc);
}

void	vm_runmain(t_vm *vm)
{
	t_proc	*proc;

	while ((vm->dump < 0 || vm->cycle < vm->dump) && ++vm->cycle
		&& (proc = --vm->nextcheck > 0 ? vm->proc : vm_livecheck(vm))
		&& (!vm->visu || update_cycles(vm)))
		while (proc || (vm->visu && key_events(vm, getch())))
		{
			if (proc->arcode && proc->cycle == vm->cycle)
			{
				(*g_inst_tab[proc->action])(vm, proc);
				vm->visu ? reverse_opcode(proc, vm, 0) : 0;
				proc->pc = proc->read;
			}
			else if (proc->cycle < vm->cycle)
			{
				proc->read = proc->pc;
				proc->action = vm_getmem(vm, 1, &proc->read).u - 1;
				if (proc->action < NBR_OP)
					vm_opinit(vm, proc, g_op_tab[proc->action]);
				else if (++proc->cycle && !(proc->arcode = 0) && !proc->pc--)
					proc->pc = MEM_SIZE - 1;
			}
			proc = proc->next;
		}
}
