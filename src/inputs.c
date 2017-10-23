/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 12:07:04 by gmichaud          #+#    #+#             */
/*   Updated: 2017/10/23 17:06:38 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "inputs.h"

int				keypress(int keycode, void *args)
{
	t_env	*env;

	env = ((t_args*)args)->env;
	if (keycode == KEY_UP)
		env->keys[0] = 1;
	if (keycode == KEY_DOWN)
		env->keys[1] = 1;
	if (keycode == KEY_LEFT)
		env->keys[2] = 1;
	if (keycode == KEY_RIGHT)
		env->keys[3] = 1;
	if (keycode == KEY_SHIFT_LEFT)
		env->keys[4] = 1;
	if (keycode == KEY_ESC)
		quit(args, EXIT_SUCCESS);
	return (1);
}

int				keyrelease(int keycode, void *args)
{
	t_env	*env;

	env = ((t_args*)args)->env;
	if (keycode == KEY_UP)
		env->keys[0] = 0;
	if (keycode == KEY_DOWN)
		env->keys[1] = 0;
	if (keycode == KEY_LEFT)
		env->keys[2] = 0;
	if (keycode == KEY_RIGHT)
		env->keys[3] = 0;
	if (keycode == KEY_SHIFT_LEFT)
		env->keys[4] = 0;
	return (1);
}
