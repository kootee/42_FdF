/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:00:40 by ktoivola          #+#    #+#             */
/*   Updated: 2024/05/15 11:28:57 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>
# include <math.h>
# include "MLX42.h"
# include "libft.h"

# define WIN_X	1080
# define WIN_Y	1080
# define WIN_MARGIN 50

# define BLACK		0x000000
# define WHITE		0xffffff
# define MAGENTA	0xff0099
# define LIGHTBLUE	0x87cefa

# define X_ISOMETRIC_ANG 30
# define Y_ISOMETRIC_ANG 330
# define Z_ISOMETRIC_ANG 30

# define DEFAULT_COLOR MAGENTA

typedef enum {
	EXIT_CMD_COUNT_ERROR = 200,
	EXIT_MAP_ALLOC_FAIL = 201,
	EXIT_MALLOC_FAIL = 202,
	EXIT_INVALID_MAP = 203
} errorcode;

typedef	enum {
	X, Y, Z
} coordinates;

typedef	enum {
	R, G, B, A
} rgb_values;

typedef	struct	colors_s {
	int32_t top;
	int32_t bottom;
	int32_t background;
}				colors_t;

typedef struct point_s {
	int32_t	color;
	int32_t	hex_color;
	float	axis[3];
}				point_t;

typedef struct map_s {
	point_t		*pt_array;
	point_t		origo;
	point_t		dim;
	colors_t	colors;
	char		*map_data;
	int			min_Z;
	int			len;
	float		scale;
}				map_t;

typedef struct fdf_s {
	mlx_t		*mlx;
	mlx_image_t	*img;
	map_t		map;	
}	fdf_t;

/* Map parse functions */
void	load_map(char *map_file_path, map_t *map);
void	init_map(map_t *map);

/* Error handling */
void	handle_error(int errno);
void	handle_map_error(map_t *map, int errno);
void	handle_error_terminate_mlx(fdf_t *fdf, int errno);

/* FDF utility functions */
bool	is_hexa_letter(char c);
void	free_strs(char **strs);
void	free_map_pts(point_t **pts);
int		round_to_int(double n);
void	validate_point(char *str, map_t *map);

/* Map utilities */
void    init_colors(map_t *map);
void    set_point_colors(map_t *map, point_t *pts, colors_t clrs, int len);
void    copy_map_points(point_t *src_pts, int len, point_t *dest_pts);

/* Draw functions */
int		draw_map(fdf_t *fdf);
int		ft_putpixel(mlx_image_t *img, float x, float y, int32_t color);

/* Colour functions */
void	set_pixel_color(uint8_t *pixel_buffer, int color, int alpha);
int32_t	set_hexcolor(char *str);
int32_t	gradient(int start_colour, int end_colour, int len, int pixel);
void	set_background(fdf_t *fdf, colors_t *color);

/* Map modification functions */
void    project_and_modify_map(fdf_t *fdf, point_t *map_projection);
void    scale_z_points(point_t *pts, map_t *map);
void    scale_points(point_t *pt_array, float scale, int len);
void    center_map(point_t *points, point_t origo, int len);

/* Matrix multiplications */
void	rot_x_axis(point_t *points, point_t *projection, float angle, int len);
void	rot_y_axis(point_t *points, point_t *projection, float angle, int len);
void	rot_z_axis(point_t *points, point_t *projection, float angle, int len);

/* For testing */
void    print_pts(point_t *pts, map_t *map);
#endif