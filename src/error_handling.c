/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 08:52:57 by ktoivola          #+#    #+#             */
/*   Updated: 2024/04/26 11:48:02 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	handle_error(int errno)
{
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	exit (EXIT_FAILURE);
	// free stuff when necessary
}

void	handle_img_error(const char *error_message, fdf_t *fdf)
{
	mlx_close_window(fdf->mlx);
	ft_putstr_fd((char *)error_message, STDERR_FILENO);
	exit (EXIT_FAILURE);
}
