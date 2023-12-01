/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_infos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 10:59:33 by tboissel          #+#    #+#             */
/*   Updated: 2019/01/31 14:18:06 by tboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	speed_gauge(t_visu *visu)
{
	int		i;

	if (!visu->fastmode)
	{
		mvwprintw(visu->infos, 8, 9, "<                              >");
		wmove(visu->infos, 8, 10);
		i = -1;
		wattron(visu->infos, COLOR_PAIR(SPEED_LEFT));
		while (++i < 3 * visu->speed)
			wprintw(visu->infos, "-");
		wattroff(visu->infos, COLOR_PAIR(SPEED_LEFT));
		wattron(visu->infos, COLOR_PAIR(SPEED_RIGHT));
		while (++i <= 30)
			wprintw(visu->infos, "-");
		wattroff(visu->infos, COLOR_PAIR(SPEED_RIGHT));
	}
	else
	{
		wattron(visu->infos, COLOR_PAIR(FASTMODE));
		mvwprintw(visu->infos, 8, 9, "     FASTMODE ACTIVATED !!!     ");
		wattroff(visu->infos, COLOR_PAIR(FASTMODE));
	}
}

void	change_speed(t_vm *vm, char key)
{
	if ((key == RIGHT_PLUS || key == LEFT_PLUS) && vm->visu->speed < 10)
	{
		vm->visu->speed++;
		speed_gauge(vm->visu);
	}
	else if (key == MINUS && vm->visu->speed)
	{
		vm->visu->speed--;
		speed_gauge(vm->visu);
	}
}

int		update_cycles(t_vm *vm)
{
	double	coef;

	coef = (double)(11 - vm->visu->speed) / 10;
	if (!vm->visu->fastmode)
		usleep(coef * 20000);
	mvwprintw(vm->visu->infos, 10, 18, "%d", vm->cycle);
	refresh();
	wrefresh(vm->visu->infos);
	return (1);
}

void	update_last_live(t_proc *proc, t_vm *vm)
{
	mvwprintw(vm->visu->infos, 16 + 6 * vm->lastlive, 18, "       ");
	wattron(vm->visu->infos, COLOR_PAIR(vm->lastlive + 1));
	mvwprintw(vm->visu->infos, 16 + 6 * (vm->lastlive), 18, "%d", proc->cycle);
	refresh();
	wrefresh(vm->visu->infos);
	wattroff(vm->visu->infos, COLOR_PAIR(vm->lastlive + 1));
}

void	update_fork(t_vm *vm)
{
	mvwprintw(vm->visu->infos, 22 + 5 * vm->pct, 18, "%d    ", vm->todie);
	mvwprintw(vm->visu->infos, 12, 18, "%d      ", vm->procct);
	refresh();
	wrefresh(vm->visu->infos);
}
