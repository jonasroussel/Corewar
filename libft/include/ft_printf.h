/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroussel <jroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 13:57:28 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/30 22:05:03 by jroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <wchar.h>
# include "libft.h"

typedef struct		s_pf_vars
{
	int		fd;
	t_byte	buff[BUFF_SIZE];
	int		pb;
	int		pf;
	int		len;
	t_byte	*output;
	char	order[6];
	char	size;
	int		width;
	int		precision;
	char	flag;
	int		options[49];
	int		olen;
	char	*prefix;
	int		prlen;
	char	*value;
	int		valen;
	int		negative;
}					t_pf_vars;
typedef struct		s_pf_func
{
	void	(*call)(t_pf_vars *, va_list *);
	char	flag;
}					t_pf_func;
typedef struct		s_pf_color
{
	char	*id;
	char	*value;
}					t_pf_color;

void				pf_write_buff(t_byte byte, t_pf_vars *vars);
void				pf_print_buff(t_pf_vars *vars);
void				pf_parse_color(const char *format, t_pf_vars *vars,
									va_list *args);
void				pf_convert(t_pf_vars *vars, va_list *args);
void				pf_format(t_pf_vars *vars);
void				pf_write_output(t_pf_vars *vars);
void				pf_create_output(t_pf_vars *vars);
void				pf_parse(const char *format, t_pf_vars *vars,
								va_list *args);
void				pf_write_unicode(t_pf_vars *vars, wchar_t wc, int size,
										int *i);
int					pf_bin_size(wchar_t wc);
int					pf_isflag(int type, char c);
void				pf_define_prefix(t_pf_vars *vars);
void				pf_init_vars(t_pf_vars *vars);
void				pf_reinit_vars(t_pf_vars *vars);
void				pf_func_s(t_pf_vars *vars, va_list *args);
void				pf_func_ss(t_pf_vars *vars, va_list *args);
void				pf_func_p(t_pf_vars *vars, va_list *args);
void				pf_func_d(t_pf_vars *vars, va_list *args);
void				pf_func_dd(t_pf_vars *vars, va_list *args);
void				pf_func_i(t_pf_vars *vars, va_list *args);
void				pf_func_o(t_pf_vars *vars, va_list *args);
void				pf_func_oo(t_pf_vars *vars, va_list *args);
void				pf_func_u(t_pf_vars *vars, va_list *args);
void				pf_func_uu(t_pf_vars *vars, va_list *args);
void				pf_func_x(t_pf_vars *vars, va_list *args);
void				pf_func_xx(t_pf_vars *vars, va_list *args);
void				pf_func_c(t_pf_vars *vars, va_list *args);
void				pf_func_cc(t_pf_vars *vars, va_list *args);
void				pf_func_percent(t_pf_vars *vars, va_list *args);
void				pf_func_n(t_pf_vars *vars, va_list *args);
void				pf_func_w(t_pf_vars *vars, va_list *args);
void				pf_func_b(t_pf_vars *vars, va_list *args);
void				pf_alt_func_c(t_pf_vars *vars, char c);

#endif
