/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 08:52:57 by ktoivola          #+#    #+#             */
/*   Updated: 2024/05/21 13:33:07 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	handle_error(t_map *map, int errno)
{
	if (errno == EXIT_CMD_COUNT_ERROR || errno == EXIT_OPEN_ERROR \
		|| errno == EXIT_INVALID_FILE_NAME)
		ft_putstr_fd("Error: Invalid file\n", STDERR_FILENO);
	else if (errno == EXIT_INVALID_MAP_DIM)
	{
		free(map->map_data);
		ft_putstr_fd("Error: Invalid map dimensions\n", STDERR_FILENO);
	}
	else if (errno == EXIT_INVALID_MAP_PTS)
	{
		free(map->map_data);
		free(map->pt_array);		
		ft_putstr_fd("Error: Invalid map points\n", STDERR_FILENO);
	}
	else
	{
		if (map->pt_array != NULL)
			free(map->pt_array);
		if (map->map_data != NULL)
			free(map->map_data);
		ft_putstr_fd("Error: Malloc/MLX fail\n", STDERR_FILENO);
	}
	exit (errno);
}

void	error_terminate_mlx(t_fdf *fdf, int errno)
{
	mlx_terminate(fdf->mlx);
	handle_error(&fdf->map, errno);
}
