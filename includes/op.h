/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 17:28:21 by twalpert          #+#    #+#             */
/*   Updated: 2019/02/11 17:20:37 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

# include "global.h"

# define REG_SIZE				4
# define REG_NUMBER				16
# define DIR_SIZE				REG_SIZE
# define IND_SIZE				2

# define T_REG_SIZE				1
# define T_DIR_SIZE				DIR_SIZE
# define T_IND_SIZE				IND_SIZE
# define T_IDX_SIZE				IND_SIZE

# define REG_CODE				0b01
# define DIR_CODE				0b10
# define IND_CODE				0b11

# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			6
# define MEM_SIZE				4096
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define COMMENT_CHARS			"#;!"
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','
# define CMD_CHAR				'.'

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING		"name"
# define COMMENT_CMD_STRING		"comment"

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

# define T_REG					0x1
# define T_DIR					0x2
# define T_IND					0x4

# define COREWAR_EXEC_MAGIC		0xea83f3
# define PROG_NAME_LENGTH		128
# define COMMENT_LENGTH			2048

# define NBR_OP					16

typedef struct			s_op
{
	char			*name;
	unsigned char	nb_arg;
	unsigned char	args[MAX_ARGS_NUMBER];
	unsigned char	opcode;
	unsigned int	cycle;
	char			*desc;
	unsigned char	ocp;
	unsigned char	index;
}						t_op;

typedef struct			s_header
{
	unsigned int	magic;
	char			name[PROG_NAME_LENGTH + 1];
	unsigned long	size;
	char			comment[COMMENT_LENGTH + 1];

}						t_header;

extern t_op				g_op_tab[NBR_OP];

#endif
