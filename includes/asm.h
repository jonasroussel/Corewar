/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 17:46:09 by jroussel          #+#    #+#             */
/*   Updated: 2019/02/15 13:48:19 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <fcntl.h>
# include <errno.h>
# include <sys/stat.h>

# include "libft.h"
# include "global.h"
# include "op.h"

/*
** Flags
*/
# define FLAG_HELP				0x1
# define FLAG_OUTPUT			0x2
# define FLAG_WERROR			0x4
# define FLAG_QUIT				0x8
# define FLAG_RECURSIVE			0x10

/*
** Errors
*/
# define NO_ERROR				0
# define READ_ERROR				0x15
# define MALLOC_ERROR			0x2a

/*
** Usages
*/
# define USAGE_BASE				0x1
# define USAGE_UNKNOW_FLAG		0x2
# define USAGE_NO_INPUT			0x4
# define USAGE_NO_OUTPUT		0x8

/*
** Errors Strings
*/
# define MALLOC_FAILED			"malloc failed!"

# define ERROR					1
# define WARNING				2

# define UNKNOW_ARG				"unknown argument"
# define EMPTY_FILE				"empty file"
# define INVALID_FILE			"invalid file"
# define INPUT_FILES			"no input files"
# define OUTPUT_DIR				"no output directory"

# define CMD_UNKNOW				"unknown command"
# define CMD_START_NUMBER		"command cannot start with number"
# define CMD_EMPTY				"empty command"
# define CMD_STRING_PARAM		"string parameter must start with '\"'"

# define CMD_NAME				1
# define NAME_REQ_STR_PARAM		".name requires a string parameter"
# define NAME_TOO_LONG			".name string too long or never closed"
# define NAME_NVR_CLOSED		".name string never closed"
# define NAME_REMAINS_CONTENT	"content after end of .name"
# define NAME_UNSET				".name is required"

# define CMD_COMMENT			2
# define COMMENT_REQ_STR_PARAM	".comment requires a string parameter"
# define COMMENT_TOO_LONG		".comment string too long or never closed"
# define COMMENT_NVR_CLOSED		".comment string never closed"
# define CONTENT_EOC			"content after end of .comment"

# define LABEL_EMPTY			"empty label"
# define LABEL_EXIST			"this label already exists"
# define LABEL_UNSET			"this label doesn't exist"
# define BAD_CHAR_LABEL			"bad character in label"

# define REQ_1_PARAM			"requires 1 parameter"
# define REQ_2_PARAM			"requires 2 parameters"
# define REQ_3_PARAM			"requires 3 parameters"
# define FIRST_PARAM_DIR		"1st parameter must be a direct value"
# define FIRST_PARAM_RED		"1st parameter must be a register"
# define INVALID_PARAM			"invalid parameter"
# define UNUSED_PARAM			"unused parameter(s)"
# define PARAM_EMPTY			"empty parameter"
# define PARAM_OOB				"value out of base"
# define PARAM_BASE_ERROR		"non-decimal negative value"
# define PARAM_REG				"this parameter must be a register"
# define PARAM_IND				"this parameter must be an indirect"
# define PARAM_DIR				"this parameter must be a direct"
# define PARAM_REG_DIR			"this parameter must be a register/direct"
# define PARAM_REG_IND			"this parameter must be a register/indirect"
# define PARAM_DIR_IND			"this parameter must be a direct/indirect"
# define PARAM_FORMAT			"bad parameter format"

# define UNKNOW_CODE			"unknown opcode"
# define SPACE_MISSING			"a blank space is missing"
# define REG_INV_VAL			"registers are from 1 to 16"
# define EMPTY_REG				"empty register"

# define OF_MAX_CHAR			"overflow 1 byte value (too large)"
# define OF_MIN_CHAR			"overflow 1 byte value (too small)"
# define OF_MAX_SHORT			"overflow 2 bytes value (too large)"
# define OF_MIN_SHORT			"overflow 2 bytes value (too small)"
# define OF_MAX_INT				"overflow 4 bytes value (too large)"
# define OF_MIN_INT				"overflow 4 bytes value (too small)"

/*
** Others
*/
# define READ_SIZE				512

# define CONTINUE				-1
# define STOP					-2
# define SORC					CONTINUE

/*
** Structures
*/
typedef struct	s_loc
{
	unsigned int	line;
	unsigned int	column;

}				t_loc;

typedef struct	s_code
{
	unsigned long	start;
	unsigned short	size;

	char			*label;

	short			index;

	t_byte			argt[3];
	t_nbr			args[3];

	unsigned int	pos[3];
	char			*refs[3];

}				t_code;

typedef struct	s_prog
{
	char			*file;
	char			*content;

	t_bool			named;
	t_bool			wrong;

	t_header		*header;
	t_list			*codes;

}				t_prog;

typedef struct	s_asm
{
	char			*name;

	short			flags;
	t_list			*programs;
	char			*output;
	int				fd;

}				t_asm;

typedef struct	s_parse
{
	unsigned int	s;
	unsigned int	j;
	int				len;
	int				ret;

}				t_parse;

typedef struct	s_vars
{
	unsigned int	i;
	unsigned int	s;
	unsigned int	j;
	unsigned int	k;

	unsigned long	start;
	t_code			*code;
	t_bool			wait_code;
	short			index;
	t_op			op;
	t_byte			type;

}				t_vars;

/*
** Assembly
*/
void			compile(t_asm *env, t_prog *prog);
unsigned long	progsize(t_prog *prog);
t_byte			codetype(t_byte type);

/*
** IO
*/
void			usage(short type, char *name, char *arg);
void			debug(t_byte type, t_prog *prog, char *err, long sign);
int				error(t_prog *prog, char *msg, t_vars *vars, long sign);
t_bool			reader(t_asm *env, t_prog *prog);
void			write_data(int fd, t_nbr data, short size);
void			write_header(t_prog *prog, int fd);
void			write_base(t_code *code, int fd);
void			write_params(t_code *code, int fd);

/*
** Memory
*/
t_bool			end(t_bool ret, t_prog *prog);
void			free_code(t_code **code);
int				quit(t_asm *env, int status);
void			init(t_asm *env, int argc, char **argv);

/*
** Tools
*/
char			*make_output(t_asm *env, char *file);
char			*dirname(char *file);
char			*basename(char *file);
void			mkdir_p(t_asm *env, char *dir);
t_loc			get_loc(char *content, unsigned int i);
char			*get_line(char *content, unsigned int i);
short			get_opindex(char *content, unsigned int start,
					unsigned int size);
short			get_size(t_code *code);
t_bool			isoneof(char c, const char *chars);
t_bool			is_comment(char c);
void			gotonxl(char *content, unsigned int *i);
int				search_start(t_prog *prog, unsigned int *i);
void			add_code(t_asm *env, t_prog *prog, t_code *code);

/*
** Parsing
*/
int				next_cmd(t_asm *env, t_prog *prog, unsigned int *i);
int				check_labels(t_prog *prog);
t_bool			parser(t_asm *env, t_prog *prog);

/*
** Code
*/
int				next_code(t_asm *env, t_prog *prog, t_vars *vars);
int				parse_label(t_asm *env, t_prog *prog, t_vars *vars);

/*
** Parameters
*/
int				next_param(t_asm *env, t_prog *prog, t_vars *vars);
int				parse_reg(t_prog *prog, t_vars *vars);
int				parse_dir(t_asm *env, t_prog *prog, t_vars *vars);
int				parse_ind(t_asm *env, t_prog *prog, t_vars *vars);
int				label_param(t_asm *env, t_prog *prog, t_vars *vars,
					unsigned short jump);

#endif
