/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:04:14 by ktoivola          #+#    #+#             */
/*   Updated: 2024/05/09 16:53:31 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <unistd.h>

void    init_projection_map(point_t *src_pts, int len, point_t *dest_pts)
{
    int i;

    i = 0;
    while (i < len)
    {
        dest_pts[i] = src_pts[i];
        printf("pt x%0.2f and y%0.2f and z%0.2f\n", src_pts[i].axis[X], src_pts[i].axis[Y], src_pts[i].axis[Z]);
        i++;
    }
}

point_t  isometric_project(point_t point)
{
 int tmp;

 tmp = point.axis[X];
 point.axis[X] = (tmp - point.axis[Y]) * cos(0.523599);
 point.axis[Y] = (tmp + point.axis[Y]) * sin(0.523599) - point.axis[Z];
 return (point);
}

/* void    set_isometric_projection(fdf_t *fdf, point_t *map_projection)
{
    // int j;
    // float transf_matrix[3][3];
    while (i < 3)
    {
        j = 0;
        while (j < 3)
        {
            transf_matrix[i][j] = 0;
            j++;
        }
        i++;
    }
    transf_matrix[0][0] = 1;
    transf_matrix[1][1] = 1;
} */

void    center_to_window(point_t *points, int len)
{
    int i;
    int x_offset;
    int y_offset;

    i = 0;
    x_offset = WIN_WIDTH / 2;
    y_offset = WIN_HEIGHT / 2;
    while(i < len)
    {
        points[i].axis[X] = points[i].axis[X] + x_offset;
        points[i].axis[Y] = points[i].axis[Y] + y_offset;
        i++;
        // what to do with Z? check from ref
    }
}

void    line(fdf_t *fdf, point_t start, point_t end)
{
    // check that the pixel is within the window
    point_t delta_v;
    point_t pixel; // the individual pixel to be drawn
    int     line;
    int     len;
    
    delta_v.axis[X] = end.axis[X] - start.axis[X];
    delta_v.axis[Y] = end.axis[Y] - start.axis[Y];
    line = sqrt((delta_v.axis[X] * delta_v.axis[X]) + \
        (delta_v.axis[Y] * delta_v.axis[Y]));
    len = line;
    delta_v.axis[X] /= line;
    delta_v.axis[Y] /= line;
    pixel.axis[X] = start.axis[X];
    pixel.axis[Y] = start.axis[Y];
    while (line > 0)
    {
        pixel.color = gradient(start.color, end.color, len, len - line);
        ft_putpixel(fdf->img, pixel.axis[X], pixel.axis[Y], pixel.color);
        // mlx_put_pixel(fdf->img, pixel.axis[X], pixel.axis[Y], pixel.color); // or ft_putpix FIX later
        pixel.axis[X] += delta_v.axis[X];
        pixel.axis[Y] += delta_v.axis[Y];
        line -= 1;
    }
}
/* Loop through columns */
void    wire(point_t *point, fdf_t *fdf, int current_line_nbr)
{
    int i;
    int x_end;
    int y_end;
    int map_width;
    int map_height;
    
    i = 0;
    map_width = (int)fdf->map.dim.axis[X];
    map_height = (int)fdf->map.dim.axis[Y];
    while(i < map_width)
    {
        x_end = i + 1;
        if (x_end >= map_width)
            x_end = map_width - 1;
        y_end = i + map_width;
        line(fdf, point[i], point[x_end]);
        if (current_line_nbr + 1 < map_height)
            line(fdf, point[i], point[y_end]);
        i++;
    }
}
/* Loop through rows */
void    draw_wires(fdf_t *fdf, point_t *map_projection)
{
    int i;
    
    i = 0;
    while (i < fdf->map.len)
    {
        wire(&map_projection[i], fdf, i / fdf->map.dim.axis[X]);
        i = i + fdf->map.dim.axis[X];
    }
}

void    scale_map(point_t *points, int scale, int len)
{
    int i;

    i = 0;
    while (i < len)
    {
        points[i].axis[X] *= scale;
        points[i].axis[Y] *= scale;
        points[i].axis[Z] *= scale;
        i++;
    }
}

int draw_map(fdf_t *fdf)
{
    int i;
    point_t *map_projection;
    
    i = 0;
    map_projection = malloc(fdf->map.len * sizeof(point_t));
    if (map_projection == NULL)
        handle_error(EXIT_MALLOC_FAIL); // go to free functions
    set_background(fdf, fdf->map.colors.background);
    init_projection_map(fdf->map.pt_array, fdf->map.len, map_projection);
    printf("printing all now");
/*     while (i < fdf->map.len)
    {
        printf("pt id is %d and stored values X: %0.4f Y: %0.4f Z: %0.4f\n", i, map_projection[i].axis[X], map_projection[i].axis[Y], map_projection[i].axis[Z]);
        printf("\n");
        i++;
    } */
    center_to_window(map_projection, fdf->map.len);
/*     while (i < fdf->map.len)
    {
        map_projection[i] = isometric_project(map_projection[i]);
    } */
    scale_map(map_projection, (int)2.5, fdf->map.len);
    draw_wires(fdf, map_projection);
    // if move on user input then move here
    return (0);
}