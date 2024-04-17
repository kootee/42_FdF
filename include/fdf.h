/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:00:40 by ktoivola          #+#    #+#             */
/*   Updated: 2024/04/17 16:53:39 by ktoivola         ###   ########.fr       */
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
# include "MLX42/MLX42.h"
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
	int	x;
	int	y;
	int	z;
	int	colour;
}				point_t;

typedef struct s_map
{
	int		**pt_array;
	int		height;
	int		width;
	int		zoom_min;
	int		zoom_max;
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

/* Map init functions */
// int	check_map(char **argv, t_fdf *fdf_args);

/* Error handling */
void	handle_error(const char *error_message);
void	handle_img_error(const char *error_message, t_fdf *fdf);

#endif