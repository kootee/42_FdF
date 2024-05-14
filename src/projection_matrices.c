/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_matrices.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 09:53:48 by ktoivola          #+#    #+#             */
/*   Updated: 2024/05/14 12:39:36 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

point_t multiply_matrix(float matrix[3][3], point_t point)
{
	int	i;
	int	j;
	point_t	mult_res;

	i = 0;
	mult_res = point;
	while(i < 3)
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

void		rot_x_axis(point_t *projection, point_t *points, float angle, int len)
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
			// printf("matrix value set to %0.2f\n", projection_matrix[i][j]);
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
	while (i++ < len)
	{	
		projection[i] = multiply_matrix(projection_matrix, points[i]);
		// printf("projection point axis %0.2f %0.2f %0.2f\n", projection[i].axis[X], projection[i].axis[Y], projection[i].axis[Z]);
	}
}

void		rot_y_axis(point_t *points, point_t *projection, float angle, int len)
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
	while (i++ < len)
	{	
		projection[i] = multiply_matrix(projection_matrix, points[i]);
		// printf("projection point axis %0.2f %0.2f %0.2f\n", projection[i].axis[X], projection[i].axis[Y], projection[i].axis[Z]);
	}
}

void		rot_z_axis(point_t *points, point_t *projection, float angle, int len)
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
	while (i++ < len)
	{	
		projection[i] = multiply_matrix(projection_matrix, points[i]);
		// printf("projection point axis %0.2f %0.2f %0.2f\n", projection[i].axis[X], projection[i].axis[Y], projection[i].axis[Z]);
	}
}
