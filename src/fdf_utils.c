/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 12:33:16 by ktoivola          #+#    #+#             */
/*   Updated: 2024/05/21 14:15:35 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_z_values(t_map *map, int idx)
{
	if (map->dim.axis[Z] < map->pt_array[idx].axis[Z])
		map->dim.axis[Z] = map->pt_array[idx].axis[Z];
	if (map->pt_array[idx].axis[Z] < map->min_z)
		map->min_z = map->pt_array[idx].axis[Z];
}

int	get_endian(void)
{
	int		endian;
	int16_t	x;

	x = 0x0001;
	endian = (*((int8_t *)(&x)) == 0x01);
	return (endian);
}

void	free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

bool	is_valid_pixel(t_point *point)
{
	if (point->axis[X] < 0 || point->axis[X] > WIN_X)
		return (false);
	if (point->axis[Y] < 0 || point->axis[Y] > WIN_Y)
		return (false);
	else
		return (true);
}
