/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroussel <jroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 17:29:05 by twalpert          #+#    #+#             */
/*   Updated: 2019/01/30 22:08:23 by jroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H

# include <fcntl.h>

# include "libft.h"
# include "op.h"

# define EMPTY_VAL		-1
# define VAL_OOB		-2
# define NEG_IN_NO_B10	-3
# define VAL_OIMAX		-4
# define VAL_OIMIN		-5

typedef union	u_nbr
{
	long			l;
	unsigned long	ul;
	t_byte			mem[8];

}				t_nbr;

typedef struct	s_coord
{
	int				x;
	int				y;
}				t_coord;

long			vtoi(char *v, int *size);
char			*fc_name(char *file, int len);

#endif
