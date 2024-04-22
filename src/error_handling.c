/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 08:52:57 by ktoivola          #+#    #+#             */
/*   Updated: 2024/04/17 17:01:12 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	handle_error(const char *error_message)
{
	ft_putstr_fd((char *)error_message, STDERR_FILENO);
	exit (EXIT_FAILURE);
	// free stuff when necessary
}

void	handle_img_error(const char *error_message, t_fdf *fdf)
{
	mlx_close_window(fdf->mlx);
	ft_putstr_fd((char *)error_message, STDERR_FILENO);
	exit (EXIT_FAILURE);
}