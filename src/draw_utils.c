/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 12:19:15 by ktoivola          #+#    #+#             */
/*   Updated: 2024/05/06 09:38:50 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include <stdint.h>

int get_endian() {
    int	endian;
	int16_t x;
	
	x = 0x0001;
	endian = *((int8_t*)(&x)) == 0x01;
	return (endian);
}

void	set_pixel_colour(char *pixel_buffer, int colour, int alpha)
{
	if (get_endian() == 0)
	{
		pixel_buffer[0] = alpha;
		pixel_buffer[1] = (colour >> 16) & 0xFF;
		pixel_buffer[2] = (colour >> 8) & 0xFF;
		pixel_buffer[3] = (colour) & 0xFF;
	}
	else
	{
		pixel_buffer[0] = (colour) & 0xFF;
		pixel_buffer[1] = (colour >> 8) & 0xFF;
		pixel_buffer[2] = (colour >> 16) & 0xFF;
		pixel_buffer[3] = alpha;
	}
}

void set_background(fdf_t *fdf)
{
	int	pixel;
	int	pixel_grid[2];
	int	background_colour;
	
	pixel_grid[X] = 0;
	pixel_grid[Y] = 0;
	background_colour = fdf->map.colours.background;
	while (pixel_grid[Y] < WIN_HEIGHT)
	{
		while (pixel_grid[X] < WIN_WIDTH)
		{
			pixel = (pixel_grid[Y] * fdf->img->width) + (pixel_grid[X] * 4);
			set_pixel_colour(fdf->img->pixels[pixel], background_colour, 1);
			pixel_grid[X]++;
		}
		pixel_grid[Y]++;
		pixel_grid[X] = 0;
	}
}

void plot_line(mlx_image_t *image, int16_t x, int16_t y, uint16_t alpha)
{
	// canvas[y][x] = 255 - (((255 - canvas[y][x]) * (alpha & 0x1FF)) >> 8);
	int32_t	colour;
	colour = 255 - ((255 * (alpha &0x1FF)) >> 8);
	mlx_put_pixel(image, x, y, colour);
}