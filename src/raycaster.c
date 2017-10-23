/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/25 09:40:52 by gmichaud          #+#    #+#             */
/*   Updated: 2017/10/19 15:45:42 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			put_pixel(t_img *img, t_vec2 pos, int color)
{
	char	*data;
	int		inc;

	data = img->data;
	inc = img->color_depth / 8;
	if (pos.x < img->width && pos.y < img->height && pos.x >= 0
		&& pos.y >= 0)
		((int*)data)[((int)(pos.y) * img->width) + (int)(pos.x)] = color;
}

static void		draw_line(t_img *img, t_vec2 top, t_vec2 bot, t_img *wall)
{
	t_vec2	line;
	double	height;
	double	y_proj;

	line.x = top.x;
	line.y = 0;
	height = bot.y - top.y;
	while (line.y < WIN_HEIGHT)
	{
		if (line.y <= top.y && line.y >= bot.y)
		{
			y_proj = (line.y * 2 - WIN_HEIGHT + height) * 95 / height;
			put_pixel(img, line,
				((int*)wall->data)[((int)y_proj) * wall->width + (int)bot.x]);
		}
		else if (line.y > bot.y)
			put_pixel(img, line, 0x00666666);
		else if (line.y < bot.y)
			put_pixel(img, line, 0x00303030);
		line.y++;
	}
}

static	double	fisheye_del(double h, double a, double dir)
{
	return (h * cos(M_PI * (360 - convert_angle(dir - a)) / 180));
}

static	void	draw_column(t_args *args, t_img *img, t_ray *ray, int orient)
{
	double	height;
	t_vec2	top;
	t_vec2	bot;

	if (orient)
	{
		ray->h_dist = fisheye_del(ray->h_dist, ray->a, args->view->dir);
		height = args->map->sq_size * 12 / ray->h_dist * args->view->dist;
		bot.x = args->map->x_offset;
	}
	else
	{
		ray->v_dist = fisheye_del(ray->v_dist, ray->a, args->view->dir);
		height = args->map->sq_size * 12 / ray->v_dist * args->view->dist;
		bot.x = args->map->y_offset;
	}
	top.x = ray->x;
	top.y = args->view->center.y + floor(height / 2);
	bot.y = args->view->center.y - floor(height / 2);
	draw_line(img, top, bot, &args->wall);
}

void			raycasting(t_args *args, t_img *img)
{
	t_ray	ray;
	double	conv_a;
	double	a_max;

	ray.x = WIN_WIDTH - 1;
	ray.a = args->view->dir - args->view->fov / 2;
	a_max = args->view->dir + args->view->fov / 2;
	while (ray.a < a_max)
	{
		conv_a = convert_angle(ray.a);
		ray.h_dist = horizontal_check(args->map, ray.a, args->view->pos);
		ray.v_dist = vertical_check(args->map, ray.a, args->view->pos);
		if (ray.h_dist != -1 && (ray.v_dist == -1 || ray.h_dist < ray.v_dist))
		{
			ray.col = conv_a > 0 && conv_a < 180 ? 0x00FF0000 : 0x00FFFF00;
			draw_column(args, img, &ray, 1);
		}
		else
		{
			ray.col = conv_a > 90 && conv_a < 270 ? 0x000000FF : 0x00FF00FF;
			draw_column(args, img, &ray, 0);
		}
		ray.x--;
		ray.a += args->view->a_pitch;
	}
}
