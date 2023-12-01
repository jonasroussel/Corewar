/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroussel <jroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 12:00:12 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/29 00:16:29 by jroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	compile(t_asm *env, t_prog *prog)
{
	t_list	*iter;
	t_code	*code;
	char	*otp;
	int		fd;

	otp = make_output(env, prog->file);
	if ((fd = open(otp, O_WRONLY | O_TRUNC | O_CREAT, 0777)) == -1)
	{
		ft_printf("%s: {lred}{bold}error:{reset} %s\n", otp, strerror(errno));
		return (free(otp));
	}
	write_header(prog, fd);
	iter = prog->codes;
	while (iter != NULL)
	{
		code = (t_code *)iter->content;
		if (code->size > 0)
		{
			write_base(code, fd);
			write_params(code, fd);
		}
		iter = iter->next;
	}
	ft_printf("%s: {lgreen}{bold}success:{reset} %s\n", prog->file, otp);
	free(otp);
}
