/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 12:19:15 by ktoivola          #+#    #+#             */
/*   Updated: 2024/05/07 12:56:18 by ktoivola         ###   ########.fr       */
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

void	set_pixel_colour(uint8_t *pixel_buffer, int colour, int alpha)
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
	background_colour = fdf->map.colors.background;
	while (pixel_grid[Y] < WIN_HEIGHT)
	{
		while (pixel_grid[X] < WIN_WIDTH)
		{
			pixel = (pixel_grid[Y] * fdf->img->width) + (pixel_grid[X] * 4);
			set_pixel_colour(&fdf->img->pixels[pixel], background_colour, 1);
			pixel_grid[X]++;
		}
		pixel_grid[Y]++;
		pixel_grid[X] = 0;
	}
}

/* int	ft_putpixel(fdf_t *fdf, point_t pixel_data)
{
	int	pixel;
	int	alpha;
	
	alpha = 0;
	if (pixel_data.axis[X] > WIN_WIDTH || pixel_data.axis[Y] > WIN_WIDTH \
		|| pixel_data.axis[X] < 0 || pixel_data.axis[Y] < 0)
		return (-1);
	pixel = ((int)pixel_data.axis[Y] * WIN_WIDTH * 4) + ((int)pixel_data.axis[X] * 4);
	set_pixel_colour(&fdf->img->pixels[pixel], pixel_data.colour, 0);
	return (0);
} */