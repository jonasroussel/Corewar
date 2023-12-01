/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hcheck.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 17:06:13 by twalpert          #+#    #+#             */
/*   Updated: 2019/01/31 13:32:57 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

int		main(void)
{
	if (REG_SIZE < 1 || REG_NUMBER < 1 || REG_NUMBER > 0xff || IND_SIZE < 1
	|| T_DIR_SIZE != DIR_SIZE || DIR_SIZE != REG_SIZE || T_IND_SIZE != IND_SIZE
	|| T_IDX_SIZE != IND_SIZE || T_REG_SIZE != 1 || REG_CODE == DIR_CODE
	|| REG_CODE == IND_CODE || DIR_CODE == IND_CODE || REG_CODE < 1
	|| REG_CODE > 3 || DIR_CODE < 1 || DIR_CODE > 3 || IND_CODE < 1
	|| IND_CODE > 3 || MAX_ARGS_NUMBER > 4 || MAX_ARGS_NUMBER < 3
	|| MAX_PLAYERS < 1 || CHAMP_MAX_SIZE < 3 || CYCLE_TO_DIE < 0
	|| CYCLE_DELTA < 0 || NBR_LIVE < 0 || MAX_CHECKS < 0
	|| CHAMP_MAX_SIZE * MAX_PLAYERS > MEM_SIZE || IDX_MOD > MEM_SIZE
	|| PROG_NAME_LENGTH < 1 || COMMENT_LENGTH < 1
	|| T_REG != 1 || T_DIR != 2 || T_IND != 4 || NBR_OP < 16)
		exit(EXIT_FAILURE);
	return (0);
}
