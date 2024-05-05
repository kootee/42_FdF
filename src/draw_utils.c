/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 12:19:15 by ktoivola          #+#    #+#             */
/*   Updated: 2024/05/04 13:24:59 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void plot_line(mlx_image_t *image, int16_t x, int16_t y, uint16_t alpha)
{
	// canvas[y][x] = 255 - (((255 - canvas[y][x]) * (alpha & 0x1FF)) >> 8);
	int32_t	colour;
	colour = 255 - ((255 * (alpha &0x1FF)) >> 8);
	mlx_put_pixel(image, x, y, colour);
}
