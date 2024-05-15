/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:04:14 by ktoivola          #+#    #+#             */
/*   Updated: 2024/05/15 11:28:09 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

bool    is_inside_window(point_t *points, int len)
{
    int i;

    i = 0;
    while (i < len)
    {
        if ((points[i].axis[X] < WIN_MARGIN) || points[i].axis[X] > WIN_X - WIN_MARGIN) 
            return (false);
        if ((points[i].axis[Y] < WIN_MARGIN) || points[i].axis[Y] > WIN_Y - WIN_MARGIN)
            return (false);
        i++;
    }
    return (true);
}

void    center_to_window(point_t *points, map_t *map)
{
    int i;
    int x_offset;
    int y_offset;
    
    i = 0;    
    x_offset = (WIN_X / 2); // - (fabsf(map->pt_array[(int)map->dim.axis[X]].axis[X] - map->pt_array[0].axis[X]) / 2);
    y_offset = (WIN_Y / 2); // - (fabsf(map->pt_array[(int)map->dim.axis[Y] * (int)map->dim.axis[X]].axis[X] - map->pt_array[0].axis[X]) / 2);
    printf("offset is %i %i\n", x_offset, y_offset);
    while(i < map->len)
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

void    fit_to_window(fdf_t *fdf, point_t *map_projection)
{
    fdf->map.origo.axis[X] = WIN_X / 2;
    fdf->map.origo.axis[Y] = WIN_Y / 2;
    fdf->map.origo.axis[Z] = 0;
    fdf->map.scale = 1;
    copy_map_points(fdf->map.pt_array, fdf->map.len, map_projection);
    project_and_modify_map(fdf, map_projection);
    while (is_inside_window(map_projection, fdf->map.len) == true)
    {        
        copy_map_points(fdf->map.pt_array, fdf->map.len, map_projection);
        project_and_modify_map(fdf, map_projection);
        fdf->map.scale += 0.2; 
    }
}
/* Loop through rows */
void    draw_wires(fdf_t *fdf, point_t *map_projection)
{
    int i;
    
    i = 0;
    fit_to_window(fdf, map_projection);
    while (i < fdf->map.len)
    {
        wire(&map_projection[i], fdf, i / fdf->map.dim.axis[X]);
        i = i + fdf->map.dim.axis[X];
    }
}

void    project_and_modify_map(fdf_t *fdf, point_t *map_projection)
{
    scale_z_points(map_projection, &fdf->map);
    rot_x_axis(map_projection, map_projection, X_ISOMETRIC_ANG, fdf->map.len);
    rot_y_axis(map_projection, map_projection, Y_ISOMETRIC_ANG, fdf->map.len);
    rot_z_axis(map_projection, map_projection, Z_ISOMETRIC_ANG, fdf->map.len);
    scale_points(map_projection, fdf->map.scale, fdf->map.len);
    center_map(map_projection, fdf->map.origo, fdf->map.len);
}

int draw_map(fdf_t *fdf)
{
    int i;
    point_t *map_projection;
    
    i = 0;
    map_projection = ft_calloc(fdf->map.len, sizeof(point_t));
    if (map_projection == NULL)
        handle_error_terminate_mlx(fdf, EXIT_MALLOC_FAIL);
    copy_map_points(fdf->map.pt_array, fdf->map.len, map_projection);
    set_background(fdf, &fdf->map.colors);
    project_and_modify_map(fdf, map_projection);
    draw_wires(fdf, map_projection);
    return (0);
}