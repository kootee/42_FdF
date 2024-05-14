/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:04:14 by ktoivola          #+#    #+#             */
/*   Updated: 2024/05/14 15:40:49 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <unistd.h>

void    project_and_modify_map(fdf_t *fdf, point_t *projected_map_pts);

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

void    print_pts(point_t *pts, map_t *map)
{
    int i = 0;
    int j = 0;
    int k = 0;
    while (i < map->len)
    {
        printf("Row %d:", k);
        while (j++ < map->dim.axis[X])
        {
            printf("    %0.1f,%0.1f,%0.1f   ", pts[i].axis[X], pts[i].axis[Y], pts[i].axis[Z]);
            i++;
        }
        printf("\n");
        k++;
        j = 0;
    }
}

void    copy_map_points(point_t *src_pts, int len, point_t *dest_pts)
{
    int i;

    i = 0;
    while (i < len)
    {
        dest_pts[i] = src_pts[i];
        // printf("pt x%0.2f and y%0.2f and z%0.2f\n", src_pts[i].axis[X], src_pts[i].axis[Y], src_pts[i].axis[Z]);
        i++;
    }
}

/* Change so that its according to angle that is given as parameter */
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
/* void    scale_map(fdf_t *fdf, float scale, int map_len)
{
    fdf->map.scale = 1; // not necessary if only done once as this is initialised
    float origo_x = fdf->map.dim.axis[X] / 2;
    float origo_y = fdf->map.dim.axis[Y] / 2;
    while(is_inside_limits(&fdf->map, map_len) == true)
    {
        scale_points(&fdf->map, map_len);
        origo_x *= fdf->map.scale;
        origo_y *= fdf->map.scale;
        if (is_inside_limits(&fdf->map, map_len) == false)
        {
            fdf->map.scale = 0.8;
            scale_points(&fdf->map, map_len);
            break ;
        }
        fdf->map.scale += 0.2;
        
        printf("scaling with 0.2\n");
        printf("scale is %f\n", fdf->map.scale);
        printf("origo scaled to %f %f\n", origo_x, origo_x);
        printf("map is now \n");
        print_pts(fdf->map.pt_array, &fdf->map);
    }
    // copy to projection
} */

void    scale_z_points(point_t *pts, map_t *map)
{
    float   proportion;
    int     divisor;
    int     i;

    i = 0;
    divisor = 1;
    proportion = map->dim.axis[Z] / map->dim.axis[X];
    if (proportion > 0.5)
        divisor = proportion * 10;
    while (i < map->len)
    {
        pts[i].axis[Z] = pts[i].axis[Z] / divisor;
        i++;
    }
}

void    center_map(point_t *points, point_t origo, int len)
{
    int i;
    i = 0;
    // printf("moving pts by x: %0.2f y: %0.2f z: %0.2f\n", origo.axis[X], origo.axis[Y], origo.axis[Z]);
    while (i < len)
    {
        points[i].axis[X] = points[i].axis[X] + origo.axis[X];
        points[i].axis[Y] = points[i].axis[Y] + origo.axis[Y];
        points[i].axis[Z] = points[i].axis[Z] + origo.axis[Z];
        i++;
    }
}

void    project_and_modify_map(fdf_t *fdf, point_t *map_projection)
{
    int i;

    i = 0;
    scale_z_points(map_projection, &fdf->map);
    // rotate_to_angle();
    rot_x_axis(map_projection, map_projection, 30, fdf->map.len);
    rot_y_axis(map_projection, map_projection, 330, fdf->map.len);
    rot_z_axis(map_projection, map_projection, 30, fdf->map.len);
/*     while (i < fdf->map.len)
    {
        map_projection[i] = isometric_project(map_projection[i]);
        i++;
    } */
    print_pts(map_projection, &fdf->map);

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
        handle_error(EXIT_MALLOC_FAIL); // go to free functions
    copy_map_points(fdf->map.pt_array, fdf->map.len, map_projection);
    set_background(fdf, fdf->map.colors.background);
    
    // printf("printing all now\n");
    // print_pts(map_projection, &fdf->map);
    
    project_and_modify_map(fdf, map_projection); // parses map and sets projection and scale etc

    draw_wires(fdf, map_projection);
    
    // printf("printing all after modifications\n");
    // print_pts(map_projection, &fdf->map);
    // if move on user input then move here
    return (0);
}