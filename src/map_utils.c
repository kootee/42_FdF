/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:00:53 by ktoivola          #+#    #+#             */
/*   Updated: 2024/05/17 16:36:31 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_path(t_map *map, char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (ft_strncmp(&str[len - 4], ".fdf", 4) != 0)
		handle_error(map, EXIT_INVALID_FILE_NAME);
}

void	init_map(t_map *map)
{
	map->len = 0;
	map->scale = 1;
	map->min_z = INT32_MAX;
	map->dim.axis[X] = 0;
	map->dim.axis[Y] = 0;
	map->dim.axis[Z] = 0;
	map->origo.axis[X] = WIN_X / 2;
	map->origo.axis[Y] = WIN_Y / 2;
	map->origo.axis[Z] = 0;
	map->map_data = NULL;
	map->pt_array = NULL;
	init_colors(map);
}

void	copy_map_points(t_point *src_pts, int len, t_point *dest_pts)
{
	int	i;

	i = 0;
	while (i < len)
	{
		dest_pts[i] = src_pts[i];
		i++;
	}
}

void	set_uneven(int idx, int line_number, t_map *map, int i)
{
	while ()
	idx++;
	map->pt_array[idx].axis[Z] = 80;
	map->pt_array[idx].axis[X] = map->dim.axis[X];
	map->pt_array[idx].axis[Y] = line_number - map->dim.axis[Y] / 2;
}

void	validate_point(char *str, t_map *map)
{
	while (*str)
	{
		if (ft_isalnum(*str) || *str == ',' || *str == '\n' || *str == '-')
		{
			if (*str >= 'G' && *str <= 'Z')
				handle_error(map, EXIT_INVALID_MAP_PTS);
			if (*str >= 'g' && *str <= 'z')
				handle_error(map, EXIT_INVALID_MAP_PTS);
		}
		else
			handle_error(map, EXIT_INVALID_MAP_PTS);
		str++;
	}
}
