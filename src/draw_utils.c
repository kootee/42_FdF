/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 12:19:15 by ktoivola          #+#    #+#             */
/*   Updated: 2024/05/08 16:33:19 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

int get_endian() {
    int	endian;
	int16_t x;
	
	x = 0x0001;
	endian = *((int8_t*)(&x)) == 0x01;
	return (endian);
}

void	set_pixel_color(uint8_t *pixel_buffer, int color, int alpha)
{

	*(pixel_buffer++) = (uint8_t)(color >> 24);
	*(pixel_buffer++) = (uint8_t)(color >> 16);
	*(pixel_buffer++) = (uint8_t)(color >> 8);
	*(pixel_buffer++) = (uint8_t)(alpha & 0xFF);
	
	/* if (get_endian() == 0)
	{
		pixel_buffer[0] = alpha;
		pixel_buffer[1] = (color >> 16) & 0xFF;
		pixel_buffer[2] = (color >> 8) & 0xFF;
		pixel_buffer[3] = (color) & 0xFF;
	}
	else
	{
		pixel_buffer[0] = (color) & 0xFF;
		pixel_buffer[1] = (color >> 8) & 0xFF;
		pixel_buffer[2] = (color >> 16) & 0xFF;
		pixel_buffer[3] = alpha;
	} */
}

void set_background(fdf_t *fdf, int background_color)
{
	int	pixel;
	int	grid[2];
	
	grid[X] = 0;
	grid[Y] = 0;
	while (grid[Y] < WIN_HEIGHT)
	{
		while (grid[X] < WIN_WIDTH)
		{
			pixel = (grid[Y] * (fdf->img->width * 4)) + (grid[X] * 4);
			set_pixel_color(&fdf->img->pixels[pixel], background_color, 50);
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
	if (x > WIN_WIDTH || y > WIN_WIDTH \
		|| x < 0 || y < 0)
		return (-1);
	pixel = ((int)y * WIN_WIDTH * 4) + ((int)x * 4);
	set_pixel_color(&img[0].pixels[pixel], color, 50);
	return (0);
}