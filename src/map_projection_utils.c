/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_projection_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:47:49 by ktoivola          #+#    #+#             */
/*   Updated: 2024/05/21 08:51:34 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

static bool	is_inside_window(t_point *points, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if ((points[i].axis[X] < WIN_MARGIN)
			|| points[i].axis[X] > WIN_X - WIN_MARGIN)
			return (false);
		if ((points[i].axis[Y] < WIN_MARGIN)
			|| points[i].axis[Y] > WIN_Y - WIN_MARGIN)
			return (false);
		i++;
	}
	return (true);
}

void	center_to_window(t_point *points, t_map *map)
{
	int	i;
	int	x_offset;
	int	y_offset;

	i = 0;
	x_offset = (WIN_X / 2);
	y_offset = (WIN_Y / 2);
	while (i < map->len)
	{
		points[i].axis[X] = points[i].axis[X] + x_offset;
		points[i].axis[Y] = points[i].axis[Y] + y_offset;
		i++;
	}
}

void	fit_to_window(t_fdf *fdf, t_point *map_projection)
{
	fdf->map.origo.axis[X] = WIN_X / 2;
	fdf->map.origo.axis[Y] = WIN_Y / 2;
	fdf->map.origo.axis[Z] = 0;
	fdf->map.scale = 1;
	copy_map_points(fdf->map.pt_array, fdf->map.len, map_projection);
	project_and_modify_map(fdf, map_projection);
	while (is_inside_window(map_projection, fdf->map.len) == true)
	{
		copy_map_points(fdf->map.pt_array, fdf->map.len, map_projection);
		project_and_modify_map(fdf, map_projection);
		if (fdf->map.len > 200000)
			fdf->map.scale = 2;
		else
			fdf->map.scale += 0.2;
		printf("scale is now %f\n", fdf->map.scale);
	}
}

void	scale_z_points(t_point *pts, t_map *map)
{
	float	proportion;
	int		divisor;
	int		i;

	i = 0;
	divisor = 1;
	proportion = map->dim.axis[Z] / map->dim.axis[X];
	if (proportion > 0.5)
		divisor = proportion * 20;
	while (i < map->len)
	{
		pts[i].axis[Z] = pts[i].axis[Z] / divisor;
		i++;
	}
}

void	scale_points(t_point *pt_array, float scale, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		pt_array[i].axis[X] *= scale;
		pt_array[i].axis[Y] *= scale;
		pt_array[i].axis[Z] *= scale;
		i++;
	}
}
