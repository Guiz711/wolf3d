/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 16:18:13 by gmichaud          #+#    #+#             */
/*   Updated: 2017/10/23 16:56:08 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	check_cell(int *data, size_t i, size_t j, int final)
{
	int neigh;

	neigh = 0;
	if (data[i * 60 + j - 1] == 1)
		neigh++;
	if (data[i * 60 + j + 1] == 1)
		neigh++;
	if (data[(i - 1) * 60 + j] == 1)
		neigh++;
	if (data[(i + 1) * 60 + j] == 1)
		neigh++;
	if (!final)
	{
		if (data[i * 60 + j] == 1)
			return ((neigh < 2 || neigh > 3) ? 0 : 1);
		if (data[i * 60 + j] == 0)
			return ((neigh == 3) ? 1 : 0);
	}
	else if (data[i * 60 + j] == 0 && neigh == 4)
		return (1);
	return (data[i * 60 + j]);
}

static void	sanitize_map(t_map *map, int final)
{
	size_t	i;
	size_t	j;

	i = 1;
	while (i < 59)
	{
		j = 1;
		while (j < 59)
		{
			map->data[i * 60 + j] = check_cell(map->data, i, j, final);
			j++;
		}
		i++;
	}
}

static void	fill_random(t_map *map)
{
	size_t i;
	size_t j;

	srand(time(NULL));
	i = 0;
	while (i < 60)
	{
		j = 0;
		while (j < 60)
		{
			if (i == 0 || i == 59 || j == 0 || j == 59)
				map->data[i * 60 + j] = 1;
			else
				map->data[i * 60 + j] = rand() % 2;
			j++;
		}
		i++;
	}
	i = 0;
	while (i++ < 5)
		sanitize_map(map, 0);
	sanitize_map(map, 1);
}

static void	choose_pos(t_args *args)
{
	int i;
	int	x;
	int	y;

	i = 1;
	while (i == 1)
	{
		x = rand() % 60;
		y = rand() % 60;
		if (args->map->data[y * 60 + x] == 0)
		{
			args->view->pos.x = (double)x * 192 + 96;
			args->view->pos.y = (double)y * 192 + 96;
			args->view->dir = rand() % 360;
			i = 0;
		}
	}
}

int			random_map(t_args *args)
{
	t_map	*map;

	if (!(map = (t_map*)malloc(sizeof(*map))))
		return (ERR_MAP);
	map->sq_size = 192;
	map->width = 60;
	map->height = 60;
	map->x_offset = 0;
	map->y_offset = 0;
	if (!(map->data = (int*)ft_memalloc(sizeof(int) * 3600)))
		return (ERR_MAP);
	fill_random(map);
	args->map = map;
	choose_pos(args);
	return (0);
}
