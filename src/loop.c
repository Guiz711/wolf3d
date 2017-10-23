/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 13:23:23 by gmichaud          #+#    #+#             */
/*   Updated: 2017/10/18 17:13:09 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	rotation(t_args *args)
{
	int		flag;

	flag = 0;
	if (args->env->keys[2])
	{
		args->view->dir += 3;
		flag = 1;
	}
	if (args->env->keys[3])
	{
		args->view->dir -= 3;
		flag = 1;
	}
	return (flag);
}

static int	forward(t_args *args, double a)
{
	t_vec2	col;
	t_vec2	new_pos;
	int		speed;

	speed = args->env->keys[4] ? 40 : 20;
	if (args->env->keys[0])
	{
		new_pos.x = args->view->pos.x + speed * cos(M_PI * a / 180);
		new_pos.y = args->view->pos.y + speed * sin(M_PI * a / 180);
		col.x = (args->view->pos.x > new_pos.x) ? -70 : 70;
		col.y = (args->view->pos.y > new_pos.y) ? -70 : 70;
		if (args->map->data[(int)((new_pos.y + col.y)
			/ args->map->sq_size) * args->map->width
			+ (int)(args->view->pos.x / args->map->sq_size)] != 1)
			args->view->pos.y = new_pos.y;
		if (args->map->data[(int)(args->view->pos.y
			/ args->map->sq_size) * args->map->width
			+ (int)((new_pos.x + col.x) / args->map->sq_size)] != 1)
			args->view->pos.x = new_pos.x;
		return (1);
	}
	return (0);
}

static int	backward(t_args *args, double a)
{
	t_vec2	col;
	t_vec2	new_pos;
	int		speed;

	speed = args->env->keys[4] ? 40 : 20;
	if (args->env->keys[1])
	{
		new_pos.x = args->view->pos.x - speed * cos(M_PI * a / 180);
		new_pos.y = args->view->pos.y - speed * sin(M_PI * a / 180);
		col.x = (args->view->pos.x > new_pos.x) ? -70 : 70;
		col.y = (args->view->pos.y > new_pos.y) ? -70 : 70;
		if (args->map->data[(int)((new_pos.y + col.y)
			/ args->map->sq_size) * args->map->width
			+ (int)((args->view->pos.x) / args->map->sq_size)] != 1)
			args->view->pos.y = new_pos.y;
		if (args->map->data[(int)((args->view->pos.y)
			/ args->map->sq_size) * args->map->width
			+ (int)((new_pos.x + col.x) / args->map->sq_size)] != 1)
			args->view->pos.x = new_pos.x;
		return (1);
	}
	return (0);
}

int			loop(void *v_args)
{
	t_args		*args;
	double		a;
	static int	flag = 1;

	args = ((t_args*)v_args);
	a = convert_angle(360 - args->view->dir);
	if (!time_interval())
		return (0);
	if (rotation(args))
		flag = 1;
	if (forward(args, a))
		flag = 1;
	if (backward(args, a))
		flag = 1;
	if (flag)
		draw_img((void*)args);
	flag = 0;
	return (1);
}
