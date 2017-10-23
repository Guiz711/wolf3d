/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 09:42:26 by gmichaud          #+#    #+#             */
/*   Updated: 2017/09/25 12:42:32 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	save_pos(char **list, t_view *view, int sq_size)
{
	size_t len;

	len = 0;
	while (list[len])
		len++;
	if (len != 4)
		return (0);
	view->pos.x = (ft_atoi(list[1]) + 1) * sq_size + sq_size / 2;
	view->pos.y = (ft_atoi(list[2]) + 1) * sq_size + sq_size / 2;
	view->dir = ft_atoi(list[3]);
	return (1);
}

static int	fill(char **line, t_map *map)
{
	size_t			i;
	static size_t	h = 1;

	i = 0;
	while (i < map->width)
	{
		if (i == 0 || i == map->width - 1)
			map->data[h * map->width + i] = 1;
		else
		{
			if (ft_strlen(line[i - 1]) > 1)
				return (0);
			map->data[h * map->width + i] = ft_atoi(line[i - 1]);
		}
		i++;
	}
	h++;
	return (1);
}

static int	process_line(char *line, t_map *map, t_view *view)
{
	char	**point_list;
	int		error;

	error = 1;
	if (!(point_list = ft_strsplit(line, ' ')))
		return (0);
	if (point_list[0] && !ft_strcmp("start_pos:", point_list[0]))
	{
		if (!save_pos(point_list, view, map->sq_size))
			error = 0;
	}
	else if (!(fill(point_list, map)))
		error = 0;
	free_point_list(&point_list);
	return (error);
}

static void	fill_borders(t_map *map)
{
	size_t i;

	i = 0;
	while (i < map->width)
	{
		map->data[i] = 1;
		i++;
	}
	i = 0;
	while (i < map->width)
	{
		map->data[(map->height - 1) * map->width + i] = 1;
		i++;
	}
}

int			read_map(char *map_file, t_map *map, t_view *view)
{
	int		fd;
	int		ret;
	int		error;
	char	*map_line;

	map_line = NULL;
	error = 1;
	if (!(map->data = (int*)ft_memalloc(sizeof(int) * map->height
		* map->width)))
		return (0);
	if ((fd = open(map_file, O_RDONLY)) == -1)
		return (0);
	fill_borders(map);
	while ((ret = get_next_line(fd, &map_line)) > 0 && error)
	{
		if (!(process_line(map_line, map, view)))
			error = 0;
		ft_memdel((void**)&map_line);
	}
	close(fd);
	if (ret == -1 || !error || view->pos.x < 0 || view->pos.y < 0)
		return (0);
	return (1);
}
