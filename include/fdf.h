/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:00:40 by ktoivola          #+#    #+#             */
/*   Updated: 2024/04/25 11:51:50 by ktoivola         ###   ########.fr       */
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

typedef struct s_mouse
{
	int	button;
	int	x;
	int	y;
	int	prev_x;
	int	prev_y;
}			t_mouse;

typedef struct s_camera
{
	int		zoom;
	double	x_angle;
	double	y_angle;
	double	z_angle;
	float	z_height;
	int		x_offset;
	int		y_offset;
	int		iso;
}			t_camera;

typedef struct point_s 
{
	int		Z;
	int16_t	colour;
}				point_t;

typedef struct s_map
{
	point_t	**pt_array;
	int		height;
	int		width;
	// int		zoom_min;
	// int		zoom_max;
}				t_map;

typedef struct s_fdf
{
	void		*mlx;
	void		*win;
	void		*img;
	t_map		*map;
	t_camera	*camera;
	t_mouse		*mouse;
	
}	t_fdf;

/* Map parse functions */
int		parse_map_file(int fd, t_fdf *fdf);
// int	check_map(char **argv, t_fdf *fdf_args);

/* Error handling */
void	handle_error(int errno);
void	handle_img_error(const char *error_message, t_fdf *fdf);

int32_t	get_colour(int32_t hex_val);

/* FDF utilities */
bool	is_hexa_letter(char c);

#endif