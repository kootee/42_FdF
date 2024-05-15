/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:22:20 by ktoivola          #+#    #+#             */
/*   Updated: 2024/05/15 11:27:21 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_putpixel(mlx_image_t *img, float x, float y, int32_t color)
{
	int	pixel;
	int	alpha;
	
	alpha = 0xFF;
	if (x > WIN_X || y > WIN_X \
		|| x < 0 || y < 0)
		return (-1);
	pixel = ((int)y * WIN_X * 4) + ((int)x * 4);
	set_pixel_color(&img->pixels[pixel], color, alpha);
	return (0);
}
void    center_map(point_t *points, point_t origo, int len)
{
    int i;
    i = 0;
    while (i < len)
    {
        points[i].axis[X] = points[i].axis[X] + origo.axis[X];
        points[i].axis[Y] = points[i].axis[Y] + origo.axis[Y];
        points[i].axis[Z] = points[i].axis[Z] + origo.axis[Z];
        i++;
    }
}

void    scale_points(point_t *pt_array, float scale, int len)
{
    int i;
    
    i = 0;
    while (i < len)
    {
        pt_array[i].axis[X] *= scale;
        pt_array[i].axis[Y] *= scale;
        pt_array[i].axis[Z] *= scale;
        i++;
    }
}

void    scale_z_points(point_t *pts, map_t *map)
{
    float   proportion;
    int     divisor;
    int     i;

    i = 0;
    divisor = 1;
    proportion = map->dim.axis[Z] / map->dim.axis[X];
    if (proportion > 0.5)
        divisor = proportion * 30;
    while (i < map->len)
    {
        pts[i].axis[Z] = pts[i].axis[Z] / divisor;
        i++;
    }
}