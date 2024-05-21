/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_projection_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:47:49 by ktoivola          #+#    #+#             */
/*   Updated: 2024/05/21 13:44:07 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	fit_to_window(t_fdf *fdf, t_point *map_projection)
{
	copy_map_points(fdf->map.pt_array, fdf->map.len, map_projection);
	project_and_modify_map(fdf, map_projection);
	while (is_inside_window(map_projection, fdf->map.len))
	{
		copy_map_points(fdf->map.pt_array, fdf->map.len, map_projection);
		project_and_modify_map(fdf, map_projection);
		fdf->map.scale += 0.2;
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
		divisor = proportion * Z_SCALE;
	while (i < map->len)
	{
		pts[i].axis[Z] = pts[i].axis[Z] / divisor;
		i++;
	}
}
void	center_map(t_point *points, t_point origo, int len)
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
