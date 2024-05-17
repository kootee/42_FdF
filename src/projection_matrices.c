/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_matrices.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 09:53:48 by ktoivola          #+#    #+#             */
/*   Updated: 2024/05/17 10:47:41 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	multiply_matrix(float matrix[3][3], t_point point)
{
	int		i;
	int		j;
	t_point	mult_res;

	i = 0;
	mult_res = point;
	while (i < 3)
	{
		mult_res.axis[i] = 0;
		mult_res.color = point.color;
		j = 0;
		while (j < 3)
		{
			mult_res.axis[i] += matrix[i][j] * point.axis[j];
			j++;
		}
		i++;
	}
	return (mult_res);
}

void	rot_x_axis(t_point *projection, t_point *points, float angle, int len)
{
	int		i;
	int		j;
	float	radius;
	float	projection_matrix[3][3];

	i = 0;
	radius = angle * M_PI / 180;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			projection_matrix[i][j] = 0;
			j++;
		}
		i++;
	}
	projection_matrix[0][0] = 1;
	projection_matrix[1][1] = cos(radius);
	projection_matrix[1][2] = -sin(radius);
	projection_matrix[2][1] = sin(radius);
	projection_matrix[2][2] = cos(radius);
	i = -1;
	while (++i < len)
		projection[i] = multiply_matrix(projection_matrix, points[i]);
}

void	rot_y_axis(t_point *points, t_point *projection, float angle, int len)
{
	int		i;
	int		j;
	float	radius;
	float	projection_matrix[3][3];

	i = 0;
	radius = angle * M_PI / 180;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			projection_matrix[i][j] = 0;
			j++;
		}
		i++;
	}
	projection_matrix[0][0] = cos(radius);
	projection_matrix[0][2] = sin(radius);
	projection_matrix[1][1] = 1;
	projection_matrix[2][0] = -sin(radius);
	projection_matrix[2][2] = cos(radius);
	i = -1;
	while (++i < len)
		projection[i] = multiply_matrix(projection_matrix, points[i]);
}

void	rot_z_axis(t_point *points, t_point *projection, float angle, int len)
{
	int		i;
	int		j;
	float	radius;
	float	projection_matrix[3][3];

	i = 0;
	radius = angle * M_PI / 180;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			projection_matrix[i][j] = 0;
			j++;
		}
		i++;
	}
	projection_matrix[0][0] = cos(radius);
	projection_matrix[0][1] = -sin(radius);
	projection_matrix[1][0] = sin(radius);
	projection_matrix[1][1] = cos(radius);
	projection_matrix[2][2] = 1;
	i = -1;
	while (++i < len)
		projection[i] = multiply_matrix(projection_matrix, points[i]);
}
