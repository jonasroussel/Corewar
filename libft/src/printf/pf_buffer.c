/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_buffer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:34:11 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/28 14:21:42 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	pf_write_buff(t_byte byte, t_pf_vars *vars)
{
	vars->buff[vars->pb] = byte;
	vars->pb++;
	vars->len++;
	if (vars->pb == BUFF_SIZE)
		pf_print_buff(vars);
}

void	pf_print_buff(t_pf_vars *vars)
{
	write(vars->fd, vars->buff, vars->pb);
	ft_bzero(vars->buff, vars->pb);
	vars->pb = 0;
}
