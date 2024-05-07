/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:00:53 by ktoivola          #+#    #+#             */
/*   Updated: 2024/05/07 13:02:39 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    init_colors(map_t *map)
{
    map->colors.background = BLACK;
    map->colors.bottom = WHITE;
    map->colors.top = MAGENTA;
}
/* Add colour to all the points, according to the Z position or given colour */
void    set_point_colors(map_t *map, point_t *points, colors_t colors, int len)
{
    int i;
    int z_len;
    
    i = 0;
    z_len = map->dim.axis[Z] - map->min_Z;
    while (i < len)
    {
        points[i].colour = DEFAULT_COLOUR;
        if (points[i].hex_colour > 0)
        {
            points[i].colour = points[i].hex_colour;
        }
        else if (points[i].axis[Z] == map->min_Z)
            points[i].colour = colors.bottom;
        else if (points[i].axis[Z] == map->dim.axis[Z])
            points[i].colour = colors.top;
        else
            points[i].colour = gradient(colors.bottom, colors.top, \
                                z_len, z_len - points[i].axis[Z]);
        i++;
    }
    /* set the rest of the colors depending on the position according to Z */
}
