/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 13:50:45 by gmichaud          #+#    #+#             */
/*   Updated: 2017/10/23 17:02:31 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		load_textures(t_args *args)
{
	int	w;

	w = args->wall.width * (COLOR_DEPTH / 8);
	if (!(args->wall.ptr = mlx_xpm_file_to_image(args->env->init,
			"./textures/wall.xpm", &args->wall.width, &args->wall.height)))
		return (0);
	if (!(args->wall.data = mlx_get_data_addr(args->wall.ptr,
			&args->wall.color_depth, &w, &args->wall.endian)))
		return (0);
	return (1);
}

static int		init_textures(t_args *args)
{
	args->wall.color_depth = 64;
	args->wall.width = 192;
	args->wall.height = 192;
	args->wall.endian = ENDIAN;
	args->wall.ptr = NULL;
	args->wall.data = NULL;
	if (!load_textures(args))
		return (0);
	return (1);
}

static void		init_keybuffer(t_env *env)
{
	size_t i;

	i = 0;
	while (i < 5)
		env->keys[i++] = 0;
}

static t_view	init_view(void)
{
	t_view	v;

	v.fov = FOV;
	v.center.x = WIN_WIDTH / 2;
	v.center.y = WIN_HEIGHT / 2;
	v.dist = fabs(v.center.x / tan(v.fov / 2));
	v.a_pitch = v.fov / WIN_WIDTH;
	v.dir = 180;
	v.pos.x = -1;
	v.pos.y = -1;
	return (v);
}

int				init_args(t_args *args, t_env *env, t_view *v)
{
	env->init = NULL;
	env->win = NULL;
	args->map = NULL;
	args->env = env;
	*v = init_view();
	args->view = v;
	init_keybuffer(env);
	if (!(env->init = mlx_init()))
		return (ERR_INIT_MLX);
	if (!(env->win = mlx_new_window(env->init, WIN_WIDTH, WIN_HEIGHT,
		"Wolf3D")))
		return (ERR_INIT_WIN);
	if (!init_textures((t_args*)args))
		return (ERR_INIT_TEXTURES);
	return (0);
}
