/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 11:09:33 by tboissel          #+#    #+#             */
/*   Updated: 2019/02/02 14:52:44 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

extern inline void	basic_init(t_vm *vm, t_visu *visu)
{
	visu->speed = 5;
	attron(A_BOLD);
	noecho();
	cbreak();
	curs_set(0);
	nodelay(visu->infos, true);
	nodelay(visu->memory, true);
	nodelay(stdscr, true);
	keypad(stdscr, true);
	keypad(visu->infos, true);
	keypad(visu->memory, true);
	refresh();
	start_color();
	init_pair(SPEED_LEFT, COLOR_GREEN, COLOR_BLACK);
	init_pair(SPEED_RIGHT, COLOR_RED, COLOR_BLACK);
	init_pair(FASTMODE, COLOR_YELLOW, COLOR_BLACK);
	init_pair(PLAYER_1, vm->pct > 4 ? COLOR_RED : COLOR_GREEN, COLOR_BLACK);
	init_pair(PLAYER_2, vm->pct > 4 ? COLOR_YELLOW : COLOR_BLUE, COLOR_BLACK);
	init_pair(PLAYER_3, vm->pct > 4 ? COLOR_GREEN : COLOR_MAGENTA, COLOR_BLACK);
	init_pair(PLAYER_4, vm->pct > 4 ? COLOR_CYAN : COLOR_RED, COLOR_BLACK);
	init_pair(PLAYER_5, COLOR_BLUE, COLOR_BLACK);
	init_pair(PLAYER_6, COLOR_MAGENTA, COLOR_BLACK);
	visu->memory = newwin(LINES, COLS > 210 ? COLS - 51 : COLS, 0, 0);
}

static inline void	init_boxes(t_vm *vm, t_visu *visu)
{
	if (COLS > 210)
		visu->infos = newwin(LINES, 50, 0, COLS - 50);
	visu->left = (COLS % 3) == 2 ? 3 : 2;
	visu->per_line = COLS / 3 - (COLS > 210 ? 18 : 1);
	wattron(visu->infos, 3);
	box(visu->infos, 0, 0);
	box(visu->memory, 0, 0);
	wrefresh(visu->infos);
	wrefresh(visu->memory);
	mvwprintw(visu->infos, 6, 2, "Speed : (+/- to change, F for fastmode)");
	speed_gauge(visu);
	mvwprintw(visu->infos, 10, 2, "Cycle : ");
	mvwprintw(visu->infos, 10, 18, "0");
	mvwprintw(visu->infos, 12, 2, "Processes : ");
	mvwprintw(visu->infos, 12, 18, "%d", vm->pct);
	mvwprintw(visu->infos, 24 + 5 * vm->pct, 2, "Cycle delta : ");
	mvwprintw(visu->infos, 26 + 5 * vm->pct, 2, "Nbr live : ");
	mvwprintw(visu->infos, 28 + 5 * vm->pct, 2, "Max checks : ");
	mvwprintw(visu->infos, 24 + 5 * vm->pct, 18, "%d", CYCLE_DELTA);
	mvwprintw(visu->infos, 26 + 5 * vm->pct, 18, "%d", NBR_LIVE);
	mvwprintw(visu->infos, 28 + 5 * vm->pct, 18, "%d", MAX_CHECKS);
	mvwprintw(visu->infos, 3, 16, "SPACEBAR TO START");
}

void				init_player_infos(t_vm *vm, t_visu *visu)
{
	int		player_nb;
	char	*name;

	player_nb = 0;
	while (++player_nb <= vm->pct)
	{
		if (!(name = strim(vm->names[player_nb - 1], 27, false)))
			vm_exit(vm, -2, vm->pct);
		wattron(visu->infos, COLOR_PAIR(player_nb));
		mvwprintw(visu->infos, 14 + 6 * (player_nb - 1), 2, "Player %d : ",
		vm->pnum[player_nb - 1]);
		mvwprintw(visu->infos, 14 + 6 * (player_nb - 1), 18, name);
		mvwprintw(visu->infos, 16 + 6 * (player_nb - 1), 6, "Last live : ---");
		wattroff(visu->infos, COLOR_PAIR(player_nb));
		free(name);
	}
}

t_visu				*init_visu(t_vm *vm)
{
	t_visu	*visu;
	int		key;

	if (!(visu = ft_memalloc(sizeof(t_visu))))
		return (NULL);
	visu->fastmode = false;
	basic_init(vm, visu);
	init_boxes(vm, visu);
	init_player_infos(vm, visu);
	mvwprintw(visu->infos, 22 + 5 * vm->pct, 2, "Cycle to die : ");
	mvwprintw(visu->infos, 22 + 5 * vm->pct, 18, "%d", CYCLE_TO_DIE);
	write_all_memory(vm, visu);
	wrefresh(visu->infos);
	wrefresh(visu->memory);
	vm->visu = visu;
	while ((key = getch()))
	{
		change_speed(vm, key);
		speed_gauge(vm->visu);
		wrefresh(vm->visu->infos);
		if (key == SPACE && (!mvwprintw(visu->infos, 3, 16, "%17s", "") || 1))
			break ;
	}
	return (visu);
}
