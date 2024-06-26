/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:22:20 by ktoivola          #+#    #+#             */
/*   Updated: 2024/05/21 14:23:55 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_putpixel(mlx_image_t *img, float x, float y, int32_t color)
{
	int	pixel;
	int	alpha;

	alpha = 0xFF;
	if (x > WIN_X || y > WIN_Y || x < 0 || y < 0)
		return ;
	pixel = ((int)round(y) * WIN_X * 4) + ((int)round(x) * 4);
	set_pixel_color(&img->pixels[pixel], color, alpha);
}

int32_t	set_hexcolor(char *str)
{
	int32_t	color;

	while (*str != ',')
		str++;
	color = ft_atoi_base(str + 3, 16);
	return (color);
}

void	line(t_fdf *fdf, t_point start, t_point end)
{
	t_point	delta_v;
	t_point	pixel;
	int		line;
	int		len;

	if (!is_valid_pixel(&start) && !is_valid_pixel(&end))
		return ;
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

