/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 11:01:03 by tboissel          #+#    #+#             */
/*   Updated: 2019/01/28 17:27:43 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char	*strim(char *str, int len, t_bool to_free)
{
	char	*new;

	if (ft_strlen(str) > (size_t)len)
	{
		if (!(new = ft_strnew((len + 3) * sizeof(char))))
			return (NULL);
		ft_memcpy(new, str, len);
		ft_memcpy(new + len, "...", 3);
		if (to_free)
			free(str);
		return (new);
	}
	else
		str = ft_strdup(str);
	return (str);
}

int		key_events(t_vm *vm, char key)
{
	if (key == F)
	{
		vm->visu->fastmode = !(vm->visu->fastmode);
		speed_gauge(vm->visu);
	}
	if (key == RIGHT_PLUS || key == LEFT_PLUS || key == MINUS)
		change_speed(vm, key);
	else if (key == SPACE)
	{
		key = 0;
		while ((key = getch()))
		{
			if (key == SPACE)
				break ;
			change_speed(vm, key);
			speed_gauge(vm->visu);
			wrefresh(vm->visu->infos);
		}
	}
	return (0);
}
