/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 12:19:15 by ktoivola          #+#    #+#             */
/*   Updated: 2024/05/14 15:03:38 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


int get_endian() 
{
    int	endian;
	int16_t x;
	
	x = 0x0001;
	endian = *((int8_t*)(&x)) == 0x01;
	return (endian);
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
	// printf("R: %02X, G: %02X, B: %02X, A: %02X\n", pixel_buffer[R], pixel_buffer[G], pixel_buffer[B], pixel_buffer[A]);
}

void set_background(fdf_t *fdf, int background_color)
{
	int	pixel;
	int	grid[2];
	
	grid[X] = 0;
	grid[Y] = 0;
	while (grid[Y] < WIN_Y)
	{
		while (grid[X] < WIN_X)
		{
			pixel = (grid[Y] * (fdf->img->width * 4)) + (grid[X] * 4);
			set_pixel_color(&fdf->img->pixels[pixel], background_color, 255);
			grid[X]++;
		}
		grid[Y]++;
		grid[X] = 0;
	}
}

int	ft_putpixel(mlx_image_t *img, float x, float y, int32_t color)
{
	int	pixel;
	int	alpha;
	
	alpha = 0xFF;
	if (x > WIN_X || y > WIN_X \
		|| x < 0 || y < 0)
		return (-1);
	pixel = ((int)y * WIN_X * 4) + ((int)x * 4);
	set_pixel_color(&img->pixels[pixel], color, 255);
	return (0);
}