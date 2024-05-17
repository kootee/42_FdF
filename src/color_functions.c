/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 12:19:15 by ktoivola          #+#    #+#             */
/*   Updated: 2024/05/17 15:59:22 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_colors(t_map *map)
{
	map->colors.background = LIGHTBLUE;
	map->colors.bottom = WHITE;
	map->colors.top = MAGENTA;
}

void	set_point_colors(t_map *map, t_point *points, t_colors colors, int len)
{
	int	i;
	int	z_len;

	i = 0;
	z_len = map->dim.axis[Z] - map->min_z;
	while (i < len)
	{
		points[i].color = DEFAULT_COLOR;
		if (points[i].hex_color > 0)
		{
			points[i].color = points[i].hex_color;
		}
		else if (points[i].axis[Z] == map->min_z)
			points[i].color = colors.bottom;
		else if (points[i].axis[Z] == map->dim.axis[Z])
			points[i].color = colors.top;
		else
			points[i].color = gradient(colors.bottom, colors.top, \
								z_len, z_len - points[i].axis[Z]);
		i++;
	}
}

int32_t	gradient(int start_color, int end_color, int len, int pixel)
{
	double	rgb_increment[3];
	int		new_color[3];
	int		pixel_color;

	rgb_increment[R] = (double)((end_color >> 16) - \
						(start_color >> 16)) / (double)len;
	rgb_increment[G] = (double)(((end_color >> 8) & 0xFF) - \
						((start_color >> 8) & 0xFF)) / (double)len;
	rgb_increment[B] = (double)((end_color & 0xFF) - \
						(start_color & 0xFF)) / (double)len;
	new_color[R] = ((start_color >> 16) & 0xFF) + \
					round_to_int(pixel * rgb_increment[R]);
	new_color[G] = ((start_color >> 8) & 0xFF) + \
					round_to_int(pixel * rgb_increment[G]);
	new_color[B] = (start_color & 0xFF) + \
					round_to_int(pixel * rgb_increment[B]);
	pixel_color = (new_color[R] << 16) + (new_color[G] << 8) + new_color[B];
	return (pixel_color);
}

void	set_pixel_color(uint8_t *pixel_buffer, int color, int alpha)
{
	if (get_endian() == 0)
	{
		pixel_buffer[R] = color;
		pixel_buffer[G] = color >> 8;
		pixel_buffer[B] = color >> 16;
		pixel_buffer[A] = alpha;
	}
	else
	{
		pixel_buffer[R] = color >> 16;
		pixel_buffer[G] = color >> 8;
		pixel_buffer[B] = color;
		pixel_buffer[A] = alpha;
	}
}

void	set_background(t_fdf *fdf, int32_t background)
{
	int	pixel;
	int	grid[2];
	int	alpha;

	alpha = 0xFF;
	grid[X] = 0;
	grid[Y] = 0;
	while (grid[Y] < WIN_Y)
	{
		while (grid[X] < WIN_X)
		{
			pixel = (grid[Y] * (fdf->img->width * 4)) + (grid[X] * 4);
			set_pixel_color(&fdf->img->pixels[pixel], background, alpha);
			grid[X]++;
		}
		grid[Y]++;
		grid[X] = 0;
	}
}
