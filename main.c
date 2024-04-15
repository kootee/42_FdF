/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:32:34 by ktoivola          #+#    #+#             */
/*   Updated: 2024/04/15 15:13:39 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	fdf_t	*fdf;

	// check and init map
	fdf = malloc(sizeof(fdf_t));
	if (argc != 2 || !check_map(argv, fdf))
	{
		ft_putstr_fd(strerror(EXIT_FAILURE), STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
	if ((fdf->mlx = mlx_init(WIDTH, HEIGHT, "FDF", true)) == NULL)
	{
		ft_putstr(mlx_strerror(mlx_errno));
		exit (EXIT_FAILURE);
	}
	// FDF loop mlx_loop_hook(mlx, ft_hook, mlx);
}