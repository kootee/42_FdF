/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:00:53 by ktoivola          #+#    #+#             */
/*   Updated: 2024/05/14 15:51:45 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_map(map_t *map)
{
	map->len = 0;
	map->scale = 1;
	map->min_Z = INT32_MAX;
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

void    init_colors(map_t *map)
{
    map->colors.background = LIGHTBLUE;
    map->colors.bottom = WHITE;
    map->colors.top = MAGENTA;
}
/* Add color to all the points, according to the Z position or given color */
void    set_point_colors(map_t *map, point_t *points, colors_t colors, int len)
{
    int i;
    int z_len;
    
    i = 0;
    z_len = map->dim.axis[Z] - map->min_Z;
    while (i < len)
    {
        points[i].color = DEFAULT_COLOR;
        if (points[i].hex_color > 0)
        {
            points[i].color = points[i].hex_color;
        }
        else if (points[i].axis[Z] == map->min_Z)
            points[i].color = colors.bottom;
        else if (points[i].axis[Z] == map->dim.axis[Z])
            points[i].color = colors.top;
        else
            points[i].color = gradient(colors.bottom, colors.top, \
                                z_len, z_len - points[i].axis[Z]);
        i++;
    }
    /* set the rest of the colors depending on the position according to Z */
}
