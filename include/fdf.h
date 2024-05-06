/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:00:40 by ktoivola          #+#    #+#             */
/*   Updated: 2024/05/06 16:03:36 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <math.h>
# include "MLX42.h"
# include "libft.h"

# define WIN_WIDTH	512
# define WIN_HEIGHT	512

# define BLACK		0x000000
# define WHITE		0xffffff
# define MAGENTA	0xff0099

# define DEFAULT_COLOUR MAGENTA

typedef enum {
	EXIT_CMD_COUNT_ERROR = 200,
	EXIT_MAP_ALLOC_FAIL = 201,
	EXIT_MALLOC_FAIL = 203,
	EXIT_INVALID_MAP = 204
} ErrorCode;

typedef	enum {
	X, Y, Z
} Coordinates;

typedef	struct	colours_s {
	int32_t top;
	int32_t bottom;
	int32_t background;
}				colours_t;

typedef struct mouse_s {
	int	button;
	int	x;
	int	y;
	int	prev_x;
	int	prev_y;
}			mouse_t;

typedef struct cam_s {
	int		zoom;
	double	x_angle;
	double	y_angle;
	double	z_angle;
	float	z_height;
	int		x_offset;
	int		y_offset;
	int		iso;
}			cam_t;

typedef struct point_s {
	float	axis[3];
	int32_t	colour;
	int32_t	hex_colour;
	bool	fill_color;
}				point_t;

typedef struct map_s {
	point_t		*pt_array;
	point_t		dim;
	colours_t	colours;
	char		*map_data;
	int			min_Z;
	int			len;
	float		scale;
	// int		zoom_min;
	// int		zoom_max;
}				map_t;

typedef struct fdf_s {
	mlx_t		*mlx;
	mlx_image_t	*img;
	map_t		map;
	void		*win; // not used?
	cam_t		*camera;
	mouse_t		*mouse;
	
}	fdf_t;

/* Map parse functions */
int		load_map(char *map_file_path, map_t *map);

/* Error handling */
void	handle_error(int errno);
void	handle_error_and_free(fdf_t *fdf, int errno);

/* FDF utility functions */
int32_t	get_colour(int32_t hex_val);
bool	is_hexa_letter(char c);
void	free_strs(char **strs);
void	free_map_pts(point_t **pts);

/* Map utilities */
void    init_colours(map_t *map);
void    set_point_colours(map_t *map);

/* Draw functions */
int		draw_map(fdf_t *fdf);
/* Map modification functions */



/* Xiaolin Wu's line drawing algorithm functions */
void	wu_line(point_t start, point_t end, mlx_image_t *img);
void	draw_wire(mlx_image_t *img, point_t start, point_t end, int16_t *xpxl1, int16_t *xpxl2,  int16_t *ypxl1, int16_t *ypxl2);

/* Drawing utilities */
void	plot_line(mlx_image_t *image, int16_t x, int16_t y, uint16_t alpha);
int		set_background(fdf_t *fdf);

#endif