/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 17:09:30 by twalpert          #+#    #+#             */
/*   Updated: 2019/02/11 18:02:33 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static long	vm_readproc(t_proc *current, int fd, char *prog, char **name)
{
	t_header	h;
	int			i;

	i = 4;
	while (i-- || !(i = 8))
		if (read(fd, (void*)&h.magic + i, 1) == -1)
			return (-1);
	read(fd, h.name, PROG_NAME_LENGTH);
	while ((h.magic == COREWAR_EXEC_MAGIC || !(h.size = ~0)) && i--)
		read(fd, (void*)&h.size + i, 1);
	if (h.magic != COREWAR_EXEC_MAGIC || h.size > CHAMP_MAX_SIZE)
		return (h.size);
	while (h.name[++i] && (i < PROG_NAME_LENGTH || (h.name[i] = 0)))
		;
	if (!read(fd, h.comment, COMMENT_LENGTH) || read(fd, &h.magic, 4) != 4
	|| read(fd, prog, CHAMP_MAX_SIZE + 1) != (ssize_t)h.size)
		return (-1);
	if (!((*name) = malloc(++i)) && write(2, "Error: memory\n", 14))
		return (-2);
	while (i--)
		(*name)[i] = h.name[i];
	close(fd);
	current->carry = 0;
	return (h.size);
}

static long	vm_loadproc(t_vm *vm, t_proc *current, int fd, int pn)
{
	char		prog[CHAMP_MAX_SIZE + 1];
	int			i;
	int			orig;

	vm->sizes[pn] = vm_readproc(current, fd, prog, &vm->names[pn]);
	if ((size_t)vm->sizes[pn] > CHAMP_MAX_SIZE)
		return (vm->sizes[pn]);
	i = MEM_SIZE / vm->pct + ((int)current->pc >= MEM_SIZE / vm->pct);
	while (i--)
		vm->mem[current->pc - i] = i >= vm->sizes[pn] ? 0 : prog[i];
	if ((orig = vm->pnum[pn]) == -1)
		vm->pnum[pn] = pn ? vm->pnum[pn - 1] + 1 : 1;
	i = pn;
	while (i--)
		if ((vm->pnum[i] == orig || vm->pnum[pn] < 0)
		&& write(2, "Error: invalid process number(s) provided\n", 42))
			vm_exit(vm, -1, pn + 1);
		else if (i == -1 && vm->pnum[pn] == vm->pnum[i] && ++vm->pnum[pn])
			i = pn;
	while (++i < REG_SIZE * REG_NUMBER)
		current->reg[i / REG_SIZE].r[i % REG_SIZE] = i < REG_SIZE ? 0xff : 0;
	current->reg[1].i = -vm->pnum[pn];
	return (0);
}

static void	vm_checkproc(t_vm *vm, t_proc *current, int pn)
{
	int		fd;
	int		l;
	long	flag;

	l = 0;
	current->next = vm->proc;
	vm->proc = current;
	current->pnum = pn;
	while (vm->names[pn][l])
		l++;
	if ((fd = open(vm->names[pn], O_RDONLY)) == -1 && write(2, "Error: \"", 8)
		&& (write(2, vm->names[pn], l) || !l) && write(2, "\" not found\n", 12))
		vm_exit(vm, -1, pn);
	current->pc = MEM_SIZE - 1 - (pn * MEM_SIZE / vm->pct);
	if ((flag = vm_loadproc(vm, current, fd, pn)))
	{
		if (write(2, "Error: ", 7) && write(2, vm->names[pn], l) && flag > 0)
			write(2, " is too large\n", 14);
		else if (flag == -1)
			write(2, " is invalid\n", 12);
		vm_exit(vm, -1, pn);
	}
	current->live = 0;
	current->cycle = 0;
	current->arcode = 0;
}

void		vm_parseargs(t_vm *vm, int argc, char **argv)
{
	int		i;

	i = 0;
	vm->names[vm->pct] = NULL;
	vm->pnum[vm->pct] = -1;
	while (argc > ++i)
		if (argv[i][0] == '-')
		{
			if (argv[i][1] == 'v' && !argv[i][2])
				vm->visu_on = 1;
			else if (argv[i][1] == 'c' && !argv[i][2])
				vm->championship = 1;
			else if (argv[i][1] == 'n' && !argv[i][2] && argc > ++i)
				vm->pnum[vm->pct] = ft_atoi_strict(argv[i]);
			else if (i < argc && argv[i][1] == 'd' && argc > ++i)
				vm->dump = ft_atoi_strict(argv[i]);
			else if (write(2, "Error: bad parameter format\n", 28))
				exit(-1);
		}
		else if (vm->pct < MAX_PLAYERS && (vm->names[vm->pct++] = argv[i]))
			vm->pnum[vm->pct] = -1;
		else if (write(2, "Error: too many champions\n", 26))
			exit(-1);
}

void		vm_initialize(t_vm *vm, int argc, char **argv)
{
	int		i;
	t_proc	*proc;

	vm->pct = 0;
	vm->visu_on = 0;
	vm->championship = 0;
	if (argc > 1 && (vm->dump = -1))
		vm_parseargs(vm, argc, argv);
	else if (write(1, "Usage: ./corewar [-dump nbr_cycles] [-v] ", 41)
		&& write(1, "[-n number] champion1.cor [...]\n", 32))
		exit(EXIT_SUCCESS);
	vm->cycle = 0;
	vm->checks = 0;
	vm->lives = 0;
	vm->proc = NULL;
	vm->todie = CYCLE_TO_DIE;
	vm->nextcheck = vm->todie;
	if (!vm->pct && write(2, "Error: please provide champions\n", 32))
		exit(-1);
	vm->lastlive = vm->pct - 1;
	i = -1;
	while (++i < vm->pct && (proc = malloc(sizeof(t_proc))))
		vm_checkproc(vm, proc, i);
	if ((vm->procct = i) != vm->pct && write(2, "Error: memory failure\n", 22))
		vm_exit(vm, -1, i);
}
