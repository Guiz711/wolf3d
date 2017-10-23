/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 09:47:55 by gmichaud          #+#    #+#             */
/*   Updated: 2017/10/23 17:14:14 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		quit(void *vargs, int status)
{
	t_args	*args;

	if (!vargs)
		exit(status);
	args = (t_args*)vargs;
	if (args->wall.ptr)
		mlx_destroy_image(args->env->init, args->wall.ptr);
	if (args->map)
	{
		if (args->map->data)
			free(args->map->data);
		free(args->map);
	}
	if (args->env->win)
		mlx_destroy_window(args->env->init, args->env->win);
	exit(status);
}

void	man(void *args)
{
	ft_putendl("first argument must be the mapfile name.");
	ft_putendl("argument \"print\" is optional, must be last argument");
	ft_putendl("if no arguments, a random map will be generated");
	quit(args, EXIT_SUCCESS);
}

void	error(void *args, int type)
{
	if (type == ERR_ARGS)
	{
		ft_putendl("arguments error.\nfirst argument must be the mapfile name");
		ft_putendl("argument \"print\" is optional, must be last argument");
		ft_putendl("if no arguments, a random map will be generated");
	}
	if (type == ERR_INIT_MLX)
		ft_putendl("error: mlx pointer could'nt be initialized");
	if (type == ERR_INIT_WIN)
		ft_putendl("error: mlx window could'nt be initialized");
	if (type == ERR_INIT_TEXTURES)
		ft_putendl("error: textures could'nt be initialized");
	if (type == ERR_MAP)
		ft_putendl("error: map could'nt be loaded");
	if (type == ERR_NAME)
	{
		ft_putendl("error: wrong map file name.");
		ft_putendl("The map has to be valid and have the .map extension.");
	}
	quit(args, EXIT_FAILURE);
}
