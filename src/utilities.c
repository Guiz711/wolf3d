/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 09:49:27 by gmichaud          #+#    #+#             */
/*   Updated: 2017/10/17 16:09:34 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	print_map(t_map *map)
{
	size_t i;
	size_t j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->data[i * map->width + j] == 1)
				ft_putchar(35);
			else
				ft_putchar(' ');
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}

int		time_interval(void)
{
	static long double	o_time = 0;
	long double			n_time;

	n_time = (long double)clock() / CLOCKS_PER_SEC;
	if (n_time - o_time >= 0.010)
	{
		o_time = n_time;
		return (1);
	}
	return (0);
}

double	ft_vec_norm(t_vec2 v1, t_vec2 v2)
{
	t_vec2	n;

	n.x = v2.x - v1.x;
	n.y = v2.y - v1.y;
	return (sqrt(n.x * n.x + n.y * n.y));
}

double	convert_angle(double a)
{
	return ((a < 0) ? 360 + fmod(a, 360) : fmod(a, 360));
}

void	free_point_list(char ***point_list)
{
	char	**tmp;

	if (!point_list)
		return ;
	tmp = *point_list;
	if (tmp)
	{
		while (*tmp)
		{
			free(*tmp);
			tmp++;
		}
		free(*point_list);
	}
	*point_list = NULL;
}
