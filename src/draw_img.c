/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 11:53:04 by gmichaud          #+#    #+#             */
/*   Updated: 2017/10/17 16:19:52 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	init_img(t_img *img, t_args *args)
{
	int		w;

	img->color_depth = COLOR_DEPTH;
	img->width = WIN_WIDTH;
	img->height = WIN_HEIGHT;
	img->endian = ENDIAN;
	img->ptr = mlx_new_image(args->env->init, img->width, img->height);
	w = img->width * (COLOR_DEPTH / 8);
	img->data = mlx_get_data_addr(img->ptr, &img->color_depth, &w,
		&img->endian);
	return (1);
}

void		draw_reticle(t_img *img)
{
	size_t	i;
	size_t	j;
	t_vec2	p;

	p.y = WIN_HEIGHT / 2 - 4;
	i = 0;
	while (i < 4)
	{
		p.x = WIN_WIDTH / 2 - 4;
		j = 0;
		while (j < 4)
		{
			put_pixel(img, p, 0x00FFFFFF);
			p.x++;
			j++;
		}
		p.y++;
		i++;
	}
}

int			draw_img(void *args)
{
	t_img	img;
	t_env	*env;

	env = ((t_args*)args)->env;
	if (!init_img(&img, (t_args*)args))
		return (0);
	raycasting((t_args*)args, &img);
	draw_reticle(&img);
	mlx_put_image_to_window(env->init, env->win, img.ptr, 0, 0);
	mlx_destroy_image(env->init, img.ptr);
	return (1);
}
