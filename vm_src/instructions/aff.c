/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 12:38:35 by twalpert          #+#    #+#             */
/*   Updated: 2019/01/21 21:30:21 by tboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	aff(t_vm *vm, t_proc *proc)
{
	if (!vm->visu && !vm->championship)
		write(1, &proc->reg[proc->args[0].i], 1);
	proc->carry = !proc->reg[proc->args[0].i].r[0];
}
