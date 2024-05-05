/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:00:53 by ktoivola          #+#    #+#             */
/*   Updated: 2024/05/02 14:30:05 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    init_colours(map_t *map)
{
    map->colours.background = BLACK;
    map->colours.bottom = WHITE;
    map->colours.top = MAGENTA;
}

void    set_colours(map_t *map)
{
    
}