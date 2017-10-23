/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 09:45:29 by gmichaud          #+#    #+#             */
/*   Updated: 2017/10/23 17:09:14 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <time.h>
# include "mlx.h"
# include "libft.h"

/*
**	Properties
*/

# define WIN_HEIGHT 1080
# define WIN_WIDTH 1920
# define FOV 60
# define COLOR_DEPTH 32
# define ENDIAN 1

# define KEYPRESSMASK (1L<<0)
# define KEYPRESS 2
# define KEYRELEASEMASK	(1L<<1)
# define KEYRELEASE	3

/*
**	Error handling
*/

# define ERR_ARGS 1
# define ERR_INIT_MLX 2
# define ERR_INIT_WIN 3
# define ERR_INIT_TEXTURES 4
# define ERR_MAP 5
# define ERR_NAME 6

typedef struct	s_vec2
{
	double		x;
	double		y;
}				t_vec2;

typedef	struct	s_ray
{
	double		a;
	double		x;
	double		h_dist;
	double		v_dist;
	int			col;
}				t_ray;

typedef struct	s_env
{
	void		*init;
	void		*win;
	int			keys[5];
}				t_env;

typedef struct	s_map
{
	int			*data;
	size_t		width;
	size_t		height;
	int			sq_size;
	int			x_offset;
	int			y_offset;
}				t_map;

typedef struct	s_view
{
	double		fov;
	t_vec2		center;
	double		dist;
	double		a_pitch;
	double		dir;
	t_vec2		pos;
}				t_view;

typedef struct	s_img
{
	void		*ptr;
	int			color_depth;
	int			width;
	int			height;
	int			endian;
	char		*data;
}				t_img;

typedef struct	s_args
{
	t_env		*env;
	t_map		*map;
	t_view		*view;
	t_img		wall;
}				t_args;

/*
**	Quit and initialize functions
*/

int				init_args(t_args *args, t_env *env, t_view *v);
void			man(void *args);
void			error(void *args, int type);
int				quit(void *args, int status);

/*
**	Events functions
*/

int				loop(void *v_args);
int				keypress(int keycode, void *args);
int				keyrelease(int keycode, void *args);
int				rot_keys(int keycode, t_args *args);

/*
**	Map handling functions
*/

int				random_map(t_args *args);
int				init_map(t_args *args, char *map_file);
int				read_map(char *map_file, t_map *map, t_view *view);
void			print_map(t_map	*map);

/*
**	Ray casting functions
*/

void			raycasting(t_args *args, t_img *img);
double			vertical_check(t_map *map, double a, t_vec2 pos);
double			horizontal_check(t_map *map, double a, t_vec2 pos);

/*
**	Mlx image handling functions
*/

int				draw_img(void *args);
void			put_pixel(t_img *img, t_vec2 pos, int color);

/*
**	Utility functions
*/

double			convert_angle(double a);
double			ft_vec_norm(t_vec2 v1, t_vec2 v2);
int				time_interval(void);
void			free_point_list(char ***point_list);

#endif
