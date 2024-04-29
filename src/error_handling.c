/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 08:52:57 by ktoivola          #+#    #+#             */
/*   Updated: 2024/04/29 14:13:45 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	handle_error(int errno)
{
	ft_printf("got to error");
	if (errno == EXIT_CMD_COUNT_ERROR)
		ft_putstr_fd("Error: Invalid command count\n", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	exit (errno);
}

void	handle_error_and_free(fdf_t *fdf, int errno)
{
	ft_printf("got to error");
	if (errno == EXIT_MAP_ALLOC_FAIL)
		free_map_pts(fdf->map->pt_array);
	mlx_terminate(fdf->mlx);
	/* needs to free map so far and the rest of fdf that's not mlx */
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	exit (EXIT_FAILURE);
}
