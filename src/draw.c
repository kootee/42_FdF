/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:04:14 by ktoivola          #+#    #+#             */
/*   Updated: 2024/05/05 13:34:17 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int set_background(fdf_t *fdf)
{
    (void)fdf;
    return (1);
}

int draw_map(fdf_t *fdf)
{
    point_t *orto_map;
    
    orto_map = malloc(fdf->map.len * sizeof(point_t));
    if (orto_map == NULL)
        handle_error(EXIT_MALLOC_FAIL);
    set_background(fdf);
    return (1);
}