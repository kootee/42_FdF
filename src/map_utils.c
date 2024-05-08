/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:00:53 by ktoivola          #+#    #+#             */
/*   Updated: 2024/05/08 16:18:17 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    init_colors(map_t *map)
{
    map->colors.background = GREEN;
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
