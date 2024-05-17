/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 08:52:57 by ktoivola          #+#    #+#             */
/*   Updated: 2024/05/17 14:09:59 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	handle_error(t_map *map, int errno)
{
	if (errno == EXIT_CMD_COUNT_ERROR)
		ft_putstr_fd("Error: Invalid command count\n", STDERR_FILENO);
	else if (errno == EXIT_OPEN_ERROR)
		ft_putstr_fd("Error: Invalid file\n", STDERR_FILENO);
	else if (errno == EXIT_INVALID_MAP)
		ft_putstr_fd("Error: Invalid map\n", STDERR_FILENO);
	else if (errno == EXIT_INVALID_MAP_DIM)
		ft_putstr_fd("Error: Invalid map dimensions\n", STDERR_FILENO);
	else if (errno == EXIT_INVALID_MAP_PTS)
		ft_putstr_fd("Error: Invalid map points\n", STDERR_FILENO);
	else if (errno == EXIT_MALLOC_FAIL)
		ft_putstr_fd("Error: Malloc fail\n", STDERR_FILENO);
	else if (errno == EXIT_INVALID_FILE_NAME)
		ft_putstr_fd("Error: Invalid file name\n", STDERR_FILENO);
	if (map->pt_array != NULL)
		free(map->pt_array);
	if (map->map_data != NULL)
		free(map->map_data);
	exit (errno);
}

void	error_terminate_mlx(t_fdf *fdf, int errno)
{
	mlx_terminate(fdf->mlx);
	handle_error(&fdf->map, errno);
}
