/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 17:28:35 by twalpert          #+#    #+#             */
/*   Updated: 2019/02/02 14:52:14 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <ncurses.h>
# include <time.h>

# include "global.h"
# include "op.h"

# define PLAYER_1 1
# define PLAYER_2 2
# define PLAYER_3 3
# define PLAYER_4 4
# define PLAYER_5 5
# define PLAYER_6 6
# define SPEED_LEFT 7
# define SPEED_RIGHT 8
# define FASTMODE 9

# define RIGHT_PLUS 43
# define LEFT_PLUS 61
# define MINUS 45
# define SPACE 32
# define F 102

typedef	union	u_reg
{
	short			s;
	int				i;
	unsigned int	u;
	unsigned char	r[REG_SIZE];
}				t_reg;

typedef struct	s_proc
{
	int				pnum;
	int				cycle;
	unsigned int	pc;
	unsigned int	read;
	t_byte			carry;
	t_byte			action;
	t_byte			arcode;
	t_byte			live;
	t_reg			args[MAX_ARGS_NUMBER];
	t_reg			reg[REG_NUMBER + 1];
	struct s_proc	*next;
	t_bool			visu;
}				t_proc;

typedef struct	s_visu
{
	WINDOW		*memory;
	WINDOW		*infos;
	int			per_line;
	int			left;
	int			speed;
	t_bool		fastmode;
}				t_visu;

typedef struct	s_vm
{
	unsigned char	mem[MEM_SIZE];
	t_proc			*proc;
	int				pnum[MAX_PLAYERS + 1];
	char			*names[MAX_PLAYERS];
	long			sizes[MAX_PLAYERS];
	int				pct;
	int				cycle;
	int				dump;
	int				lives;
	int				todie;
	int				nextcheck;
	int				checks;
	int				procct;
	t_visu			*visu;
	t_byte			visu_on;
	t_byte			lastlive;
	t_byte			championship;
}				t_vm;

typedef void	(*t_inst)(t_vm*, t_proc *proc);

extern t_inst	g_inst_tab[];

void			vm_initialize(t_vm *vm, int argc, char **argv);
t_reg			vm_getmem(t_vm *vm, int n, unsigned int *pc);
void			vm_putmem(t_vm *vm, t_reg val, unsigned int pc, t_proc *proc);
void			vm_indmod(t_proc *proc, t_reg *arg, int mod);
void			vm_runmain(t_vm *vm);
void			vm_opinit(t_vm *vm, t_proc *proc, t_op op);
int				ft_atoi_strict(const char *a);
void			vm_exit(t_vm *vm, int code, int i);

void			live(t_vm *vm, t_proc *proc);
void			ld(t_vm *vm, t_proc *proc);
void			st(t_vm *vm, t_proc *proc);
void			add(t_vm *vm, t_proc *proc);
void			sub(t_vm *vm, t_proc *proc);
void			and(t_vm *vm, t_proc *proc);
void			or(t_vm *vm, t_proc *proc);
void			xor(t_vm *vm, t_proc *proc);
void			zjmp(t_vm *vm, t_proc *proc);
void			ldi(t_vm *vm, t_proc *proc);
void			sti(t_vm *vm, t_proc *proc);
void			proc_fork(t_vm *vm, t_proc *proc);
void			lld(t_vm *vm, t_proc *proc);
void			lldi(t_vm *vm, t_proc *proc);
void			lfork(t_vm *vm, t_proc *proc);
void			aff(t_vm *vm, t_proc *proc);

t_visu			*init_visu(t_vm *vm);
int				update_cycles(t_vm *vm);
void			write_mem(t_vm *vm, t_proc *proc, unsigned int pc, t_byte *val);
void			update_fork(t_vm *vm);
int				key_events(t_vm *vm, char key);
void			update_last_live(t_proc *proc, t_vm *vm);
void			write_all_memory(t_vm *vm, t_visu *visu);
char			*get_player_name(t_proc *proc, int i);
long			get_player_size(t_proc *proc, int i);
void			speed_gauge(t_visu *visu);
void			change_speed(t_vm *vm, char key);
void			reverse_opcode(t_proc *proc, t_vm *vm, t_byte rev);
char			*strim(char *str, int len, t_bool to_free);

#endif
