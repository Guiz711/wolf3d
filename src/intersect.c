/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 11:49:19 by gmichaud          #+#    #+#             */
/*   Updated: 2017/10/18 17:17:00 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

double			get_dist(t_vec2 inter, t_vec2 pos, t_map *map, int orient)
{
	if (orient)
		map->y_offset = (int)inter.y % map->sq_size;
	else
		map->x_offset = (int)inter.x % map->sq_size;
	return (ft_vec_norm(pos, inter));
}

static t_vec2	h_first_intersect(double a, t_vec2 pos, int sq_size)
{
	t_vec2	intersect;

	if (a > 0 && a < 180)
		intersect.y = floor(pos.y / sq_size) * sq_size - 0.00001;
	else if (a > 180 && a < 360)
		intersect.y = floor(pos.y / sq_size) * sq_size + sq_size;
	intersect.x = pos.x + (pos.y - intersect.y) / tan(M_PI * a / 180);
	return (intersect);
}

double			horizontal_check(t_map *map, double a, t_vec2 pos)
{
	t_vec2	inter;
	double	x_step;
	double	y_step;

	a = convert_angle(a);
	if (a == 0 || a == 180)
		return (-1);
	inter = h_first_intersect(a, pos, map->sq_size);
	y_step = (a > 0 && a < 180) ? -map->sq_size : map->sq_size;
	x_step = map->sq_size / tan(M_PI * a / 180);
	if (a > 90 && a < 270)
		x_step = x_step < 0 ? x_step : -x_step;
	else
		x_step = x_step > 0 ? x_step : -x_step;
	while (inter.x >= 0 && inter.x < map->width * map->sq_size && inter.y >= 0
		&& inter.y < map->height * map->sq_size)
	{
		if (map->data[(int)(inter.y / map->sq_size) * map->width
			+ (int)(inter.x / map->sq_size)] == 1)
			return (get_dist(inter, pos, map, 0));
		inter.x += x_step;
		inter.y += y_step;
	}
	return (-1);
}

static t_vec2	v_first_intersect(double a, t_vec2 pos, int sq_size)
{
	t_vec2	intersect;

	if (a > 90 && a < 270)
		intersect.x = floor(pos.x / sq_size) * sq_size - 0.00001;
	else
		intersect.x = floor(pos.x / sq_size) * sq_size + sq_size;
	intersect.y = pos.y + (pos.x - intersect.x) * tan(M_PI * a / 180);
	return (intersect);
}

double			vertical_check(t_map *map, double a, t_vec2 pos)
{
	t_vec2	inter;
	double	x_step;
	double	y_step;

	a = convert_angle(a);
	if (a == 90 || a == 270)
		return (-1);
	inter = v_first_intersect(a, pos, map->sq_size);
	x_step = (a > 90 && a < 270) ? -map->sq_size : map->sq_size;
	y_step = x_step * tan(M_PI * a / 180);
	if (a >= 0 && a < 180)
		y_step = y_step < 0 ? y_step : -y_step;
	else
		y_step = y_step > 0 ? y_step : -y_step;
	while (inter.x >= 0 && inter.x < map->width * map->sq_size
		&& inter.y >= 0 && inter.y < map->height * map->sq_size)
	{
		if (map->data[(int)(inter.y / map->sq_size) * map->width
			+ (int)(inter.x / map->sq_size)] == 1)
			return (get_dist(inter, pos, map, 1));
		inter.x += x_step;
		inter.y += y_step;
	}
	return (-1);
}
