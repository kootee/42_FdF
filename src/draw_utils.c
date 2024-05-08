/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 12:19:15 by ktoivola          #+#    #+#             */
/*   Updated: 2024/05/08 15:32:05 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int32_t	gradient(int start_colour, int end_colour, int len, int pixel)
{
	double	rgb_increment[3];
	int		new_colour[3];
	int		pixel_colour;
	
	rgb_increment[R] = (double)((end_colour >> 16) - \
						(start_colour >> 16)) / (double)len;
	rgb_increment[G] = (double)(((end_colour >> 8) & 0xFF) - \
						((start_colour >> 8) & 0xFF)) / (double)len;
	rgb_increment[B] = (double)((end_colour & 0xFF) - \
						(start_colour & 0xFF)) / (double)len;
	new_colour[R] = ((start_colour >> 16) & 0xFF) + \
					round_to_int(pixel * rgb_increment[R]);
	new_colour[G] = ((start_colour >> 8) & 0xFF) + \
					round_to_int(pixel * rgb_increment[G]);
	new_colour[B] = (start_colour & 0xFF) + \
					round_to_int(pixel * rgb_increment[B]);
	pixel_colour = (new_colour[R] << 16) + (new_colour[G] << 8) + new_colour[B];
	return (pixel_colour);
}

int get_endian() {
    int	endian;
	int16_t x;
	
	x = 0x0001;
	endian = *((int8_t*)(&x)) == 0x01;
	return (endian);
}

void	set_pixel_colour(uint8_t *pixel_buffer, int color, int alpha)
{

	*(pixel_buffer++) = (uint8_t)(color >> 24);
	*(pixel_buffer++) = (uint8_t)(color >> 16);
	*(pixel_buffer++) = (uint8_t)(color >> 8);
	*(pixel_buffer++) = (uint8_t)(alpha & 0xFF);
	
	/* if (get_endian() == 0)
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
	} */
}

void set_background(fdf_t *fdf)
{
	int	pixel;
	int	pixel_grid[2];
	int	background_colour;
	
	pixel_grid[X] = 0;
	pixel_grid[Y] = 0;
	background_colour = fdf->map.colors.background;
	while (pixel_grid[Y] < WIN_HEIGHT)
	{
		while (pixel_grid[X] < WIN_WIDTH)
		{
			pixel = (pixel_grid[Y] * fdf->img->width) + (pixel_grid[X] * 4);
			set_pixel_colour(&fdf->img->pixels[pixel], background_colour, 50);
			pixel_grid[X]++;
		}
		pixel_grid[Y]++;
		pixel_grid[X] = 0;
	}
}

int	ft_putpixel(mlx_image_t *img, float x, float y, int32_t color)
{
	int	pixel;
	int	alpha;
	
	alpha = 0xFF;
	if (x > WIN_WIDTH || y > WIN_WIDTH \
		|| x < 0 || y < 0)
		return (-1);
	pixel = ((int)y * WIN_WIDTH * 4) + ((int)x * 4);
	set_pixel_colour(&img[0].pixels[pixel], color, 50);
	return (0);
}