/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_inst_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 17:07:46 by twalpert          #+#    #+#             */
/*   Updated: 2019/01/21 19:27:58 by tboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_inst	g_inst_tab[] =
{
	&live,
	&ld,
	&st,
	&add,
	&sub,
	&and,
	&or,
	&xor,
	&zjmp,
	&ldi,
	&sti,
	&proc_fork,
	&lld,
	&lldi,
	&lfork,
	&aff
};
