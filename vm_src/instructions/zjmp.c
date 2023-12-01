/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 14:54:44 by twalpert          #+#    #+#             */
/*   Updated: 2019/01/28 13:23:15 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	zjmp(t_vm *vm, t_proc *proc)
{
	(void)vm;
	if (proc->carry)
	{
		vm_indmod(proc, &proc->args[0], IDX_MOD);
		proc->read = proc->args[0].u;
	}
}
