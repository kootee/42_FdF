/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 08:52:57 by ktoivola          #+#    #+#             */
/*   Updated: 2024/04/27 14:25:58 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	handle_error(int errno)
{
	if ()
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	exit (EXIT_FAILURE);
	// free stuff when necessary
}

void	handle_error_and_free(fdf_t *fdf, int errno)
{
	
}

void	handle_img_error(const char *error_message, fdf_t *fdf)
{
	mlx_close_window(fdf->mlx);
	ft_putstr_fd((char *)error_message, STDERR_FILENO);
	exit (EXIT_FAILURE);
}
