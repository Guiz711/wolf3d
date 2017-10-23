/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 10:09:16 by gmichaud          #+#    #+#             */
/*   Updated: 2017/10/23 16:19:03 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	verify_extension(char *map_file)
{
	map_file += ft_strlen(map_file) - 4;
	if (ft_strcmp(map_file, ".map"))
		return (0);
	return (1);
}

static int	line_size(char *map_line, t_map *map)
{
	size_t	w;

	w = 0;
	while (map_line[w])
		w++;
	if (map->width == 0 && map->height == 0)
		map->width = (size_t)(ceil((float)w / 2));
	else if (map->width != (size_t)(ceil((float)w / 2)))
		return (-1);
	return (0);
}

static int	get_map_size(char *map_file, t_map *map)
{
	int		fd;
	int		ret;
	int		err;
	char	*map_line;

	err = 0;
	map_line = NULL;
	if ((fd = open(map_file, O_RDONLY)) == -1)
		return (0);
	while (!err && (ret = get_next_line(fd, &map_line)) > 0)
	{
		if (!strstr(map_line, "start_pos:"))
		{
			err = line_size(map_line, map);
			map->height++;
		}
		free(map_line);
	}
	close(fd);
	if (ret == -1 || err == -1 || map->width == 0 || map->height == 0)
		return (0);
	map->height += 2;
	map->width += 2;
	return (1);
}

int			init_map(t_args *args, char *map_file)
{
	t_map	*map;

	map = NULL;
	if (!map_file)
		return (ERR_NAME);
	if (!verify_extension(map_file))
		return (ERR_NAME);
	if (!(map = (t_map*)malloc(sizeof(*map))))
		return (ERR_MAP);
	map->sq_size = 192;
	map->data = NULL;
	map->width = 0;
	map->height = 0;
	map->x_offset = 0;
	map->y_offset = 0;
	if (!get_map_size(map_file, map))
		return (ERR_MAP);
	if (!read_map(map_file, map, args->view))
		return (ERR_MAP);
	args->map = map;
	return (0);
}
