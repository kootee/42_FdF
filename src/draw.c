/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:46:57 by ktoivola          #+#    #+#             */
/*   Updated: 2024/05/03 16:21:26 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void plot(int16_t x, int16_t y, uint16_t alpha)
{
	// image [y , x] = put_colour;
}

static bool	is_steep(point_t start, point_t end)
{
	int32_t	dx;
	int32_t	dy;
	
	if (end.axis[Y] > start.axis[Y])
		dy = end.axis[Y] - start.axis[Y];
	else
		dy = start.axis[Y] - end.axis[Y];
	if (end.axis[X] > start.axis[X])
		dx = end.axis[X] - start.axis[X];
	else
		dx = end.axis[X] - start.axis[X];
	if (dy > dx)
		return (true);
	else
		return (false);
}

void	swap_values(point_t start, point_t end, int32_t *z, bool steep)
{
	if (steep)
	{
		*z = start.axis[X]; 
		start.axis[X] = start.axis[Y]; 
		start.axis[Y] = z; 
		*z = end.axis[X]; 
		end.axis[X] = end.axis[Y]; 
		end.axis[Y] = z;
	}
	else
	{
		*z = start.axis[X]; 
		start.axis[X] = end.axis[X];
		end.axis[X] = z; 
		*z = start.axis[Y]; 
		start.axis[Y] = end.axis[Y]; 
		end.axis[Y] = z;
	}
}

void	first_point(point_t start, point_t end, int32_t gradient, bool steep)
{
	/* Handle first point */
	int32_t inter_y;
	int32_t	x_end = (start.axis[X] + 0x8000) & 0xFFFF0000;
	int32_t	y_end = start.axis[Y] + ((gradient * (x_end - start.axis[X])) >> 16);
	int32_t	x_gap = 0x10000 - ((start.axis[X] + 0x8000) & 0xFFFF);
	int16_t	xpxl1 = end.axis[X] >> 16;
	int16_t ypxl1 = end.axis[Y] >> 16;
	if (steep)
	{
		plot(ypxl1, xpxl1, 0x100 - (((0x100 - ((y_end >> 8) & 0xFF)) * x_gap) >> 16));
		plot(ypxl1 + 1, xpxl1, 0x100 - ((((y_end >> 8) & 0xFF)  * x_gap) >> 16));
	}
	else
	{
		plot(xpxl1, ypxl1, 0x100 - (((0x100 - ((y_end >> 8) & 0xFF)) * x_gap) >> 16));
		plot(xpxl1, ypxl1 + 1, 0x100 - ((((y_end >> 8) & 0xFF)  * x_gap) >> 16));
	}
	inter_y = y_end + gradient;
}

void	second_point(point_t start, point_t end, int32_t gradient, bool steep)
{
	
}

void	draw_wire(point_t start, point_t end)
{
	int32_t	z;
	int32_t	dx;
	int32_t	dy;
	int32_t	gradient;
	bool	steep;
	
	steep = is_steep(start, end);
	
	if (steep)
		swap_values(start, end, &z, true);
	else if (start.axis[X] > end.axis[X])
		swap_values(start, end, &z, false);
	
	dx = end.axis[X] - start.axis[X]; // length of X
	dy = end.axis[Y] - start.axis[Y]; // lenght of y
	
	if ((dx >> 8) == 0)
		gradient = 0x10000;
	else
		gradient = (dy << 8) / (dx >> 8);

	first_point(start, end, gradient, steep);
}
