/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:00:40 by ktoivola          #+#    #+#             */
/*   Updated: 2024/04/16 17:09:48 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
/**
 * Main MLX handle, carries important data in regards to the program.
 * @param window The window itself.
 * @param context Abstracted opengl data.
 * @param width The width of the window.
 * @param height The height of the window.
 * @param delta_time The time difference between the previous frame and the current frame.
 */
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include "MLX42/MLX42.h"
# include "libft.h"

# define WIDTH 512
# define HEIGHT 512

typedef struct fdf_s
{
	mlx_t	*mlx;
	map_t	*map;
}	fdf_t;

typedef struct point_s 
{
	int	x;
	int	y;
	int	z;
	int	colour;
}				point_t;

typedef struct map_s
{
	int		**pt_array;
	int		height;
	int		width;
	int		zoom_min;
	int		zoom_max;
}				map_t;

/* Map init functions */

int	check_map(char **argv, fdf_t *fdf_args);

#endif