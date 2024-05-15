/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:04:14 by ktoivola          #+#    #+#             */
/*   Updated: 2024/05/15 14:45:41 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_point_wire(point_t *point, fdf_t *fdf, int current_line)
{
	int	i;
	int	x_end;
	int	y_end;
	int	map_width;
	int	map_height;

	i = 0;
	map_width = (int)fdf->map.dim.axis[X];
	map_height = (int)fdf->map.dim.axis[Y];
	while (i < map_width)
	{
		x_end = i + 1;
		if (x_end >= map_width)
			x_end = map_width - 1;
		y_end = i + map_width;
		line(fdf, point[i], point[x_end]);
		if (current_line + 1 < map_height)
			line(fdf, point[i], point[y_end]);
		i++;
	}
}

static void	draw_wires(fdf_t *fdf, point_t *map_projection)
{
	int	i;

	i = 0;
	fit_to_window(fdf, map_projection);
	while (i < fdf->map.len)
	{
		draw_point_wire(&map_projection[i], fdf, i / fdf->map.dim.axis[X]);
		i = i + fdf->map.dim.axis[X];
	}
}

static void	center_map(point_t *points, point_t origo, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		points[i].axis[X] = points[i].axis[X] + origo.axis[X];
		points[i].axis[Y] = points[i].axis[Y] + origo.axis[Y];
		points[i].axis[Z] = points[i].axis[Z] + origo.axis[Z];
		i++;
	}
}

void	project_and_modify_map(fdf_t *fdf, point_t *map_projection)
{
	scale_z_points(map_projection, &fdf->map);
	rot_x_axis(map_projection, map_projection, X_ISOMETRIC_ANG, fdf->map.len);
	rot_y_axis(map_projection, map_projection, Y_ISOMETRIC_ANG, fdf->map.len);
	rot_z_axis(map_projection, map_projection, Z_ISOMETRIC_ANG, fdf->map.len);
	scale_points(map_projection, fdf->map.scale, fdf->map.len);
	center_map(map_projection, fdf->map.origo, fdf->map.len);
}

int	draw_map(fdf_t *fdf)
{
	int		i;
	point_t	*map_projection;

	i = 0;
	map_projection = ft_calloc(fdf->map.len, sizeof(point_t));
	if (map_projection == NULL)
		handle_error_terminate_mlx(fdf, EXIT_MALLOC_FAIL);
	copy_map_points(fdf->map.pt_array, fdf->map.len, map_projection);
	set_background(fdf, fdf->map.colors.background);
	project_and_modify_map(fdf, map_projection);
	draw_wires(fdf, map_projection);
	return (EXIT_SUCCESS);
}
