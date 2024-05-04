/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wu_line.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:46:57 by ktoivola          #+#    #+#             */
/*   Updated: 2024/05/04 14:07:08 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	wu_line(point_t start, point_t end, mlx_image_t *image)
{
	int32_t	x;
	int16_t	xpxl1;
	int16_t	xpxl2;
	int16_t	ypxl1;
	int16_t	ypxl2;

	draw_wire(image, start, end, &xpxl1, &xpxl2, &ypxl1, &ypxl2);
}
