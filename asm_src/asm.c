/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 12:00:09 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/28 14:19:25 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	main(int argc, char **argv)
{
	t_asm	env;
	t_list	*iter;
	t_prog	*prog;

	init(&env, argc, argv);
	iter = env.programs;
	while (iter)
	{
		prog = (t_prog *)iter->content;
		if (reader(&env, prog))
		{
			if (parser(&env, prog))
			{
				close(env.fd);
				if (!prog->wrong)
				{
					if (env.output)
						mkdir_p(&env, env.output);
					compile(&env, prog);
				}
			}
		}
		iter = iter->next;
	}
	return (quit(&env, NO_ERROR));
}
