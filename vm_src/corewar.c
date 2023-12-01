/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 17:09:30 by twalpert          #+#    #+#             */
/*   Updated: 2019/02/02 14:53:02 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

extern inline void	dump(t_vm vm)
{
	int		win;
	int		i;
	char	c;

	if (!vm.proc && (win = vm.lastlive) >= 0 && write(1, "Champion ", 9))
	{
		i = 1;
		while (i * 10 <= vm.pnum[win])
			i *= 10;
		while (i && (c = (vm.pnum[win] / i) % 10 + '0') && write(1, &c, 1))
			i /= 10;
		while (vm.names[win][i])
			i++;
		if (write(1, ": ", 2) && (write(1, vm.names[win], i) || !i))
			write(1, " wins!\n", 7);
	}
	i = MEM_SIZE;
	while (vm.dump >= 0 && i--)
	{
		c = vm.mem[i] / 16 + (vm.mem[i] / 16 > 9 ? 'a' - 10 : '0');
		write(1, &c, 1);
		c = vm.mem[i] % 16 + (vm.mem[i] % 16 > 9 ? 'a' - 10 : '0');
		write(1, &c, 1);
		write(1, i % 32 ? " " : "\n", 1);
	}
}

void				write_winner(t_vm *vm)
{
	mvwprintw(vm->visu->infos, 10, 18, "%d", vm->cycle);
	wattron(vm->visu->infos, COLOR_PAIR(vm->lastlive + 1));
	wattron(vm->visu->infos, A_REVERSE);
	mvwprintw(vm->visu->infos, 2, 2, " The winner is ");
	wprintw(vm->visu->infos, "%s ", vm->names[vm->lastlive]);
	mvwprintw(vm->visu->infos, 4, 2, " Press any key to quit ");
	wattroff(vm->visu->infos, COLOR_PAIR(vm->lastlive + 1));
	wattroff(vm->visu->infos, A_REVERSE);
	refresh();
	wrefresh(vm->visu->infos);
	while ((getch() == -1))
		;
	endwin();
	if (COLS <= 210)
		dump(*vm);
}

int					main(int argc, char **argv)
{
	t_vm	vm;

	vm_initialize(&vm, argc, argv);
	if (vm.visu_on || (vm.visu = NULL))
	{
		initscr();
		if ((COLS - (COLS > 210 ? 54 : 2)) / 3 * (LINES - 2) < MEM_SIZE
			&& write(2, "Window too small for visualizer\n", 32)
			&& !(vm.visu = NULL))
			endwin();
		else if (vm.pct <= 6 && (vm.visu = init_visu(&vm)))
			nodelay(vm.visu->infos, true);
		else if (write(2, "Visualizer failed to initialize\n", 32))
			endwin();
	}
	vm_runmain(&vm);
	if (vm.visu)
		write_winner(&vm);
	else
		dump(vm);
	vm_exit(&vm, vm.championship ? vm.lastlive : 0, vm.pct);
}
