/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:00:40 by ktoivola          #+#    #+#             */
/*   Updated: 2024/05/21 13:52:30 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdbool.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>
# include "libft.h"
# include "MLX42.h"

# define WIN_X	1080
# define WIN_Y	1080
# define WIN_MARGIN 50

# define BLACK		0x000000
# define WHITE		0xffffff
# define MAGENTA	0xff0099
# define LIGHTBLUE	0x87cefa
# define GREEN		0x00ff00

# define DEFAULT_COLOR BLACK

# define Z_SCALE	20
# define X_ISOMETRIC_ANG 30
# define Y_ISOMETRIC_ANG 330
# define Z_ISOMETRIC_ANG 30

typedef enum s_errorcode
{
	EXIT_CMD_COUNT_ERROR = 200,
	EXIT_MALLOC_FAIL = 201,
	EXIT_INVALID_MAP_PTS = 202,
	EXIT_INVALID_MAP_DIM = 203,
	EXIT_OPEN_ERROR = 204,
	EXIT_INVALID_FILE_NAME = 205
}	t_errorcode;

typedef enum s_coordinates
{
	X,
	Y,
	Z
}	t_coordinates;

typedef enum s_rgb_values
{
	R,
	G,
	B,
	A
}	t_rgb_values;

typedef struct s_colors
{
	int32_t	top;
	int32_t	bottom;
	int32_t	background;
	int32_t	base;
}	t_colors;

typedef struct s_point
{
	int32_t	color;
	int32_t	hex_color;
	float	axis[3];
}	t_point;

typedef struct s_map
{
	t_point		*pt_array;
	t_point		origo;
	t_point		dim;
	t_colors	colors;
	char		*map_data;
	int			min_z;
	int			len;
	float		scale;
}	t_map;

typedef struct s_fdf
{
	mlx_t		*mlx;
	t_map		map;	
	mlx_image_t	*img;
}	t_fdf;

/* Map parse */
void	load_map(char *map_file_path, t_map *map);

/* Map utilities */
void	init_map(t_map *map);
void	copy_map_points(t_point *src_pts, int len, t_point *dest_pts);
void	validate_point(char *str, t_map *map);
void	set_uneven(int idx, int line_number, t_map *map);
void	check_path(t_map *map, char *str);

/* Draw */
void	draw_map(t_fdf *fdf, t_point *map_projection);
void	line(t_fdf *fdf, t_point start, t_point end);
void	ft_putpixel(mlx_image_t *img, float x, float y, int32_t color);

/* Colour */
void	init_colors(t_map *map);
void	set_background(t_fdf *fdf, int32_t background);
void	set_point_colors(t_map *map, t_point *pts, t_colors clrs);
void	set_pixel_color(uint8_t *pixel_buffer, int color, int alpha);
int32_t	gradient(int start_colour, int end_colour, int len, int pixel);
int32_t	set_hexcolor(char *str);

/* Map modification/projection */
void	project_and_modify_map(t_fdf *fdf, t_point *map_projection);
void	scale_z_points(t_point *pts, t_map *map);
void	scale_points(t_point *pt_array, float scale, int len);
void	fit_to_window(t_fdf *fdf, t_point *map_projection);
void	center_map(t_point *points, t_point origo, int len);

/* Matrix multiplications */
void	rot_x_axis(t_point *points, t_point *projection, float angle, int len);
void	rot_y_axis(t_point *points, t_point *projection, float angle, int len);
void	rot_z_axis(t_point *points, t_point *projection, float angle, int len);

/* FDF utilities */
bool	is_hexa_letter(char c);
int		get_endian(void);
void	free_strs(char **strs);
void	set_z_values(t_map *map, int idx);
bool	is_valid_pixel(t_point *point);

/* Error handling */
void	handle_error(t_map *map, int errno);
void	error_terminate_mlx(t_fdf *fdf, int errno);

#endif