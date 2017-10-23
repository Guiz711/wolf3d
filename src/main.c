/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 09:44:07 by gmichaud          #+#    #+#             */
/*   Updated: 2017/10/23 16:39:04 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		events(void *args)
{
	t_env	*env;

	env = ((t_args*)args)->env;
	mlx_hook(env->win, 17, 0L, &quit, args);
	mlx_hook(env->win, KEYPRESS, KEYPRESSMASK, &keypress, args);
	mlx_hook(env->win, KEYRELEASE, KEYRELEASEMASK, &keyrelease, args);
	mlx_loop_hook(env->init, &loop, args);
	mlx_loop(env->init);
}

int				main(int argc, char **argv)
{
	t_env	env;
	t_args	args;
	t_view	v;
	int		err_type;

	if ((argc == 3 && ft_strcmp("print", argv[2])) || argc > 3)
		error(NULL, ERR_ARGS);
	if (argc == 2 && !ft_strcmp("man", argv[1]))
		man(NULL);
	if ((err_type = init_args(&args, &env, &v)))
		error(&args, err_type);
	if (argc == 1 || (argc == 2 && !ft_strcmp("print", argv[1])))
	{
		if ((err_type = random_map(&args)))
			error(&args, err_type);
	}
	else if ((argc == 2 && ft_strcmp("print", argv[1])) || argc == 3)
	{
		if ((err_type = init_map(&args, argv[1])))
			error(&args, err_type);
	}
	if (argc == 3 || (argc == 2 && !ft_strcmp("print", argv[1])))
		print_map(args.map);
	events(&args);
	return (0);
}
