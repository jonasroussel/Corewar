/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 10:28:39 by twalpert          #+#    #+#             */
/*   Updated: 2019/02/15 14:03:29 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	vm_exit(t_vm *vm, int code, int i)
{
	t_proc	*proc;

	while (i--)
		free(vm->names[i]);
	while ((proc = vm->proc))
	{
		vm->proc = proc->next;
		free(proc);
	}
	if (code == -2 && vm->visu)
		free(vm->visu);
	exit(code);
}

t_reg	vm_getmem(t_vm *vm, int n, unsigned int *pc)
{
	int		i;
	t_reg	val;
	t_byte	flag;

	i = REG_SIZE;
	flag = vm->mem[*pc] >> 7 ? 0xFF : 0;
	val.i = flag ? -1 : 0;
	while (i-- > n)
		val.r[i] = flag;
	while (n-- && ((val.r[n] = vm->mem[*pc]) || 1))
		*pc = (*pc ? *pc : MEM_SIZE) - 1;
	return (val);
}

void	vm_putmem(t_vm *vm, t_reg val, unsigned int pc, t_proc *proc)
{
	int		i;
	int		pos;

	i = REG_SIZE;
	while (i--)
	{
		vm->mem[pc] = val.r[i];
		pc = (pc ? pc : MEM_SIZE) - 1;
	}
	pos = (pc + REG_SIZE) % MEM_SIZE + 1;
	if (vm->visu)
		write_mem(vm, proc, pos, val.r);
}

void	vm_indmod(t_proc *proc, t_reg *arg, int mod)
{
	t_byte			flag;
	t_byte			neg;
	unsigned int	rem;
	int				i;

	i = -1;
	neg = arg->r[REG_SIZE - 1] >> 7;
	rem = 1;
	while (neg && ++i < REG_SIZE)
	{
		flag = rem;
		rem = (~arg->r[i] + flag) > 0xff;
		arg->r[i] = ~arg->r[i] + flag;
	}
	i = REG_SIZE;
	rem = 0;
	while (i--)
		rem = (rem * 0x100 + arg->r[i]) % mod;
	arg->i = proc->pc + (neg ? rem : -rem);
	if (arg->i < 0 || arg->i >= MEM_SIZE)
		arg->i += arg->i < 0 ? MEM_SIZE : -MEM_SIZE;
}

int		ft_atoi_strict(const char *a)
{
	int		res;
	int		i;

	i = 0;
	res = 0;
	while (a && res >= 0 && a[i] >= '0' && a[i] <= '9' && ((res *= 10) || !res))
		res += a[i++] - '0';
	if ((!a || a[i] || res < 0) && write(2, "Error: bad numeric input\n", 25))
		exit(-1);
	return (res);
}
