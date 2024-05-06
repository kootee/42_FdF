/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:00:53 by ktoivola          #+#    #+#             */
/*   Updated: 2024/05/06 10:50:49 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    init_colours(map_t *map)
{
    map->colours.background = BLACK;
    map->colours.bottom = WHITE;
    map->colours.top = MAGENTA;
}
/* Add colour to all the points, according to the Z position or given colour */
void    set_point_colours(map_t *map)
{
    int i;
    
    i = 0;
    while (i < map->len)
    {
        init_point_colour((int)map->dim.axis[Z], map->min_Z, &map->pt_array[i], \
        map->colours);
        i++;
    }
}

void    init_point_colour(int max_z, int min_z, point_t *point, colours_t colours)
{
    point->fill_color = true;
    point->colour = DEFAULT_COLOUR;
    if (point->hex_colour > 0)
    {
        point->colour = point->hex_colour;
        return;
    }
    /* set the rest of the colours depending on the position according to Z */
}