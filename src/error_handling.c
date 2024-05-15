/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 08:52:57 by ktoivola          #+#    #+#             */
/*   Updated: 2024/05/15 10:33:59 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	handle_error(int errno)
{
	if (errno == EXIT_CMD_COUNT_ERROR)
		ft_putstr_fd("Error: Invalid command count\n", STDERR_FILENO);
	if (errno == EXIT_INVALID_MAP)
		ft_putstr_fd("Error: Invalid map\n", STDERR_FILENO);
	else
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
	exit (errno);
}
void	handle_map_error(map_t *map, int errno)
{
	free(map->map_data);
	free(map->pt_array);
	handle_error(errno);
}
void	handle_error_terminate_mlx(fdf_t *fdf, int errno)
{
	mlx_terminate(fdf->mlx);
	handle_map_error(&fdf->map, errno);
}
