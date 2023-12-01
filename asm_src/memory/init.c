/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroussel <jroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 12:00:14 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/29 00:16:36 by jroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	donext(t_asm *env, char *arg, short next)
{
	t_prog	prog;
	t_list	*node;

	if (next == 0)
	{
		ft_bzero(&prog, sizeof(t_prog));
		if (!(prog.file = ft_strdup(arg)))
			quit(env, MALLOC_ERROR);
		if (!(prog.header = (t_header *)ft_memalloc(sizeof(t_header))))
			quit(env, MALLOC_ERROR);
		if (!(node = ft_lstnew(&prog, sizeof(t_prog))))
			quit(env, MALLOC_ERROR);
		ft_lstpush(&env->programs, node);
	}
	if (next == FLAG_OUTPUT && env->output == NULL)
		if (!(env->output = ft_strdup(arg)))
			quit(env, MALLOC_ERROR);
}

static void	detect(t_asm *env, char **argv, int i, short *next)
{
	if (ft_equal(argv[i], "--output") || ft_equal(argv[i], "-o"))
		env->flags |= (*next = FLAG_OUTPUT);
	else if (ft_equal(argv[i], "--Werror") || ft_equal(argv[i], "-W"))
		env->flags |= FLAG_WERROR;
	else if (ft_equal(argv[i], "--quit") || ft_equal(argv[i], "-q"))
		env->flags |= FLAG_QUIT;
	else if (ft_equal(argv[i], "--recursive") || ft_equal(argv[i], "-r"))
		env->flags |= FLAG_RECURSIVE;
	else if (ft_equal(argv[i], "-qW") || ft_equal(argv[i], "-Wq"))
		env->flags |= FLAG_WERROR | FLAG_QUIT;
	else if (ft_equal(argv[i], "-Wr") || ft_equal(argv[i], "-rW"))
		env->flags |= FLAG_WERROR | FLAG_RECURSIVE;
	else if (ft_equal(argv[i], "-qr") || ft_equal(argv[i], "-rq"))
		env->flags |= FLAG_QUIT | FLAG_RECURSIVE;
	else if (ft_equal(argv[i], "-Wqr") || ft_equal(argv[i], "-Wrq")
			|| ft_equal(argv[i], "-qWr") || ft_equal(argv[i], "-qrW")
			|| ft_equal(argv[i], "-rWq") || ft_equal(argv[i], "-rqW"))
		env->flags |= FLAG_WERROR | FLAG_QUIT | FLAG_RECURSIVE;
	else
		usage(USAGE_UNKNOW_FLAG, argv[0], argv[i]);
}

static void	flags(t_asm *env, int argc, char **argv)
{
	int		i;
	short	next;

	i = 1;
	next = 0;
	while (i < argc)
	{
		if (argv[i][0] == '-')
			detect(env, argv, i, &next);
		else
		{
			donext(env, argv[i], next);
			next = 0;
		}
		i++;
	}
}

static void	iferrors(t_asm *env, char *av0)
{
	short	errors;

	errors = 0;
	if (env->programs == NULL)
		errors |= USAGE_NO_INPUT;
	if (env->flags & FLAG_OUTPUT && env->output == NULL)
		errors |= USAGE_NO_OUTPUT;
	if (errors)
	{
		usage(errors, av0, NULL);
		quit(env, errors);
	}
}

void		init(t_asm *env, int argc, char **argv)
{
	int		i;

	i = 1;
	while (i < argc)
		if (ft_equal(argv[i++], "--help"))
			usage(USAGE_BASE, argv[0], NULL);
	ft_bzero(env, sizeof(t_asm));
	if (!(env->name = ft_strdup(argv[0])))
		quit(env, MALLOC_ERROR);
	flags(env, argc, argv);
	iferrors(env, argv[0]);
}
