/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 19:17:16 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/28 14:19:40 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"

char	*fc_name(char *file, int len)
{
	int		fd;
	char	tmp[4 + PROG_NAME_LENGTH];
	int		i;

	if (len + 3 > PROG_NAME_LENGTH)
		return (NULL);
	fd = open(file, O_RDONLY);
	read(fd, tmp, sizeof(tmp));
	i = 0;
	while (tmp[i + 4] != 0)
	{
		if (!ft_isascii(tmp[i + 4]))
			return (NULL);
		if (i >= len)
		{
			ft_memset(tmp + i + 4, '.', 3);
			i += 3;
			break ;
		}
		i++;
	}
	close(fd);
	return (ft_strsub(tmp, 4, i));
}
