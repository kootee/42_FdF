/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wu_line_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 12:20:38 by ktoivola          #+#    #+#             */
/*   Updated: 2024/05/04 14:34:20 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static bool	is_steep(point_t start, point_t end)
{
	if (fabsf(end.axis[Y] - start.axis[Y]) > fabsf(end.axis[X] - start.axis[X]))
		return (true);
	else 
		return (false);
}

void	swap_values(point_t start, point_t end, float *z, bool steep)
{
	if (steep)
	{
		*z = start.axis[X]; 
		start.axis[X] = start.axis[Y]; 
		start.axis[Y] = *z; 
		*z = end.axis[X]; 
		end.axis[X] = end.axis[Y]; 
		end.axis[Y] = *z;
	}
	else
	{
		*z = start.axis[X]; 
		start.axis[X] = end.axis[X];
		end.axis[X] = *z; 
		*z = start.axis[Y]; 
		start.axis[Y] = end.axis[Y]; 
		end.axis[Y] = *z;
	}
}

int32_t	first_point(mlx_image_t *img, point_t start, point_t end, int32_t gradient, bool steep, int16_t *xpxl1, int16_t *xpxl2, int16_t *ypxl1, int16_t *ypxl2)
{
	/* Handle first point */
	uint16_t	x_end = round(start.axis[X]);
	float		y_end = start.axis[Y] + gradient * ((float)x_end - start.axis[X]);
	float		x_gap = 1.0 - (start.axis[X] + 0.5 - floor(start.axis[X] + 0.5));
	
	*xpxl1 = x_end;
	*ypxl1 = floor(y_end);
	
	if (steep)
	{
		plot_line(img, *ypxl1, *xpxl1, (1.0 - (y_end - floor(y_end))) * x_gap);
		plot_line(img, *ypxl1 + 1, *xpxl1, (y_end - floor(y_end))  * x_gap);
	}
	else
	{
		plot_line(img, *xpxl1, *ypxl1, (1.0 - (y_end - floor(y_end))) * x_gap);
		plot_line(img, *xpxl1 + 1, *ypxl1, (y_end - floor(y_end))  * x_gap);
	}
	return(y_end + gradient);
}

void	second_point(mlx_image_t *img, point_t start, point_t end, int32_t gradient, bool steep, int16_t *xpxl1, int16_t *xpxl2, int16_t *ypxl1, int16_t *ypxl2)
{
	uint16_t x_end;
	float	 y_end;
	float	 x_gap;

	x_end = round(end.axis[X]);
	y_end = end.axis[Y] + gradient * ((float)x_end - end.axis[X]);
	x_gap = end.axis[X] + 0.5 - floor(end.axis[X] + 0.5);
	
	*xpxl2 = x_end;
	*ypxl2 = floor(y_end);
	if (steep)
	{
		plot_line(img, *ypxl2, *xpxl2, (1.0 - (y_end - floor(y_end))) * x_gap);
		plot_line(img, *ypxl2 + 1, *xpxl2, (y_end - floor(y_end))  * x_gap);
	}
	else
	{
		plot_line(img, *xpxl2, *ypxl2, (1.0 - (y_end - floor(y_end))) * x_gap);
		plot_line(img, *xpxl2 + 1, *ypxl2, (y_end - floor(y_end))  * x_gap);
	}
	
}

void	draw_wire(mlx_image_t *img, point_t start, point_t end, int16_t *xpxl1, int16_t *xpxl2, int16_t *ypxl1, int16_t *ypxl2)
{
	float		z;
	float		dx;
	float		dy;
	float		gradient;
	float		inter_y;
	bool		steep;
	uint16_t	x;
	
	steep = is_steep(start, end);
	if (steep)
		swap_values(start, end, &z, true);
	else if (start.axis[X] > end.axis[X])
		swap_values(start, end, &z, false);
	dx = end.axis[X] - start.axis[X]; // length of X
	dy = end.axis[Y] - start.axis[Y]; // lenght of y
	if (dx == 0.0)
		gradient = 1;
	else 
		gradient = dy / dx;
		
	inter_y = first_point(img, start, end, gradient, steep, xpxl1, xpxl2, ypxl1, ypxl2);
	second_point(img, start, end, gradient, steep, xpxl1, xpxl2, ypxl1, ypxl2);
	// main loop
	x = *xpxl1 + 1;
	if (steep)
	{
		while (x < *xpxl2)
		{
			plot_line(img, floor(inter_y), x, (1.0 - (inter_y - floor(inter_y))));
			plot_line(img, floor(inter_y) + 1, x, (inter_y - floor(inter_y)));
			inter_y += gradient;
			x++;
		}
	}
	else
	{
		while (x < *xpxl2)
		{
			plot_line(img, x, floor(inter_y), (1.0 - (inter_y - floor(inter_y))));
			plot_line(img, x, floor(inter_y) + 1, (inter_y - floor(inter_y)));
			inter_y += gradient;
			x++;
		}
	}
}

/* 
Q16 implementation

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
		start.axis[Y] = *z; 
		*z = end.axis[X]; 
		end.axis[X] = end.axis[Y]; 
		end.axis[Y] = *z;
	}
	else
	{
		*z = start.axis[X]; 
		start.axis[X] = end.axis[X];
		end.axis[X] = *z; 
		*z = start.axis[Y]; 
		start.axis[Y] = end.axis[Y]; 
		end.axis[Y] = *z;
	}
}

int32_t	first_point(mlx_image_t *img, point_t start, point_t end, int32_t gradient, bool steep)
{
	int32_t	x_end = (start.axis[X] + 0x8000) & 0xFFFF0000;
	int32_t	y_end = start.axis[Y] + ((gradient * (x_end - start.axis[X])) >> 16);
	int32_t	x_gap = 0x10000 - ((start.axis[X] + 0x8000) & 0xFFFF);
	int16_t	xpxl1 = end.axis[X] >> 16;
	int16_t ypxl1 = end.axis[Y] >> 16;
	if (steep)
	{
		plot_line(img, ypxl1, xpxl1, 0x100 - (((0x100 - ((y_end >> 8) & 0xFF)) * x_gap) >> 16));
		plot_line(img, ypxl1 + 1, xpxl1, 0x100 - ((((y_end >> 8) & 0xFF)  * x_gap) >> 16));
	}
	else
	{
		plot_line(img, xpxl1, ypxl1, 0x100 - (((0x100 - ((y_end >> 8) & 0xFF)) * x_gap) >> 16));
		plot_line(img, xpxl1, ypxl1 + 1, 0x100 - ((((y_end >> 8) & 0xFF)  * x_gap) >> 16));
	}
	return(y_end + gradient);
}

void	second_point(mlx_image_t *img, point_t start, point_t end, int32_t gradient, bool steep)
{
	int32_t x_end;
	int32_t y_end;
	int32_t x_gap;
	int16_t	xpxl2;
	int32_t	ypxl2;

	x_end = (end.axis[X] + 0x8000) & 0xFFFF0000;
	y_end = end.axis[Y] + (gradient * (x_end - end.axis[X]) >> 16);
	x_gap = (end.axis[X] + 0x8000) & 0xFFFF;
	xpxl2 = x_end >> 16;
	ypxl2 = y_end >> 16;
	if (steep)
	{
		plot_line(img, ypxl2, xpxl2, 0x100 - (((0x100 - ((y_end >> 8) & 0xFF)) * x_gap) >> 16));
		plot_line(img, ypxl2 + 1, xpxl2, 0x100 - ((((y_end >> 8) & 0xFF)  * x_gap) >> 16));
	}
	else
	{
		plot_line(img, xpxl2, ypxl2, 0x100 - (((0x100 - ((y_end >> 8) & 0xFF)) * x_gap) >> 16));
		plot_line(img, xpxl2, ypxl2 + 1, 0x100 - ((((y_end >> 8) & 0xFF)  * x_gap) >> 16));
	}
	
}

void	draw_wire(mlx_image_t *img, point_t start, point_t end, int32_t *xpxl1, int32_t *xpxl2)
{
	int32_t		z;
	int32_t		dx;
	int32_t		dy;
	int32_t		inter_y;
	int32_t		gradient;
	int32_t		x;
	bool		steep;
	
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
	inter_y = first_point(img, start, end, gradient, steep);
	second_point(img, start, end, gradient, steep);
	x = *xpxl1 + 1;
	if (steep)
	{
		while (x < *xpxl2)
		{
			plot_line(img, (inter_y >> 16), x, (inter_y >> 8) & 0xFF);
			plot_line(img, (inter_y >>16) + 1, x, 0x100 - ((inter_y >> 8) & 0xFF));
			inter_y += gradient;
			x++;
		}
	}
	else
	{
		while (x < *xpxl2)
		{
			plot_line(img, x, (inter_y >> 16), (inter_y >> 8) & 0xFF);
			plot_line(img, x, (inter_y >>16) + 1, 0x100 - ((inter_y >> 8) & 0xFF));
			x++;
			inter_y += gradient;
		}
		
	}
} */