/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:00:53 by ktoivola          #+#    #+#             */
/*   Updated: 2024/05/17 10:58:57 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_map(t_map *map)
{
	map->len = 0;
	map->scale = 1;
	map->min_z = INT32_MAX;
	map->dim.axis[X] = 0;
	map->dim.axis[Y] = 0;
	map->dim.axis[Z] = 0;
	map->origo.axis[X] = WIN_X / 2;
	map->origo.axis[Y] = WIN_Y / 2;
	map->origo.axis[Z] = 0;
	map->map_data = NULL;
	map->pt_array = NULL;
	init_colors(map);
}

void	copy_map_points(t_point *src_pts, int len, t_point *dest_pts)
{
	int	i;

	i = 0;
	while (i < len)
	{
		dest_pts[i] = src_pts[i];
		i++;
	}
}

void	init_colors(t_map *map)
{
	map->colors.background = LIGHTBLUE;
	map->colors.bottom = WHITE;
	map->colors.top = MAGENTA;
}

/* Add color to all the points, according to the Z position or given color */
/* set the rest of the colors depending on the position according to Z */
void	set_point_colors(t_map *map, t_point *points, t_colors colors, int len)
{
	int	i;
	int	z_len;

	i = 0;
	z_len = map->dim.axis[Z] - map->min_z;
	while (i < len)
	{
		points[i].color = DEFAULT_COLOR;
		if (points[i].hex_color > 0)
		{
			points[i].color = points[i].hex_color;
		}
		else if (points[i].axis[Z] == map->min_z)
			points[i].color = colors.bottom;
		else if (points[i].axis[Z] == map->dim.axis[Z])
			points[i].color = colors.top;
		else
			points[i].color = gradient(colors.bottom, colors.top, \
								z_len, z_len - points[i].axis[Z]);
		i++;
	}
}

void	validate_point(char *str, t_map *map)
{
	while (*str)
	{
		if (ft_isalnum(*str) || *str == ',' || *str == '\n' || *str == '-')
		{
			if (*str > 'G' && *str < 'Z')
				handle_map_error(map, EXIT_INVALID_MAP);
		}
		else
			handle_map_error(map, EXIT_INVALID_MAP);
		str++;
	}
}
