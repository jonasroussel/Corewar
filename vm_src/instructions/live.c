/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 12:37:21 by twalpert          #+#    #+#             */
/*   Updated: 2019/01/28 17:14:18 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	live(t_vm *vm, t_proc *proc)
{
	int		pnum;
	int		i;

	proc->live = 1;
	vm->lives++;
	i = REG_SIZE;
	while (i-- > 4)
		if (proc->args[0].r[i] != 0xff)
			return ;
	i = vm->pct;
	while (i-- && -proc->args[0].i != vm->pnum[i])
		;
	if ((pnum = i) != -1)
	{
		i = 0;
		while (!vm->visu_on && !vm->championship && vm->names[pnum][i])
			i++;
		vm->lastlive = pnum;
		if (vm->visu)
			update_last_live(proc, vm);
		else if ((i && write(1, vm->names[pnum], i))
			|| (!vm->championship && !vm->visu_on))
			write(1, " reporting in.\n", 15);
	}
}
