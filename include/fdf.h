/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:00:40 by ktoivola          #+#    #+#             */
/*   Updated: 2024/04/27 14:44:20 by ktoivola         ###   ########.fr       */
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
# include "MLX42.h"
# include "libft.h"

# define WIDTH 100
# define HEIGHT 100
/* 
typedef enum {
	EXIT_CMD_COUNT_ERROR = 900,
	MAP_ALLOC_FAIL = 901
} ErrorCode; */

typedef struct mouse_s
{
	int	button;
	int	x;
	int	y;
	int	prev_x;
	int	prev_y;
}			mouse_t;

typedef struct cam_s
{
	int		zoom;
	double	x_angle;
	double	y_angle;
	double	z_angle;
	float	z_height;
	int		x_offset;
	int		y_offset;
	int		iso;
}			cam_t;

typedef struct point_s 
{
	int		Z;
	bool	last;
	int32_t	colour;
}				point_t;

typedef struct map_s
{
	point_t	**pt_array;
	int		height;
	int		width;
	// int		zoom_min;
	// int		zoom_max;
}				map_t;

typedef struct fdf_s
{
	void	*mlx;
	void	*win;
	void	*img;
	map_t	*map;
	cam_t	*camera;
	mouse_t	*mouse;
	
}	fdf_t;

/* Map parse functions */
int		parse_map_file(int fd, fdf_t *fdf);

/* Error handling */
void	handle_error(int errno);
void	handle_img_error(const char *error_message, fdf_t *fdf);

/* FDF utility functions */
bool	is_hexa_letter(char c);
int32_t	get_colour(int32_t hex_val);

#endif