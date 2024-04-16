/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:32:34 by ktoivola          #+#    #+#             */
/*   Updated: 2024/04/16 16:49:19 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	init_fdf(fdf_t *fdf)
{
	fdf = malloc(sizeof(fdf_t));
	if (fdf == NULL)
		return (-1);
	fdf->map->height = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	fdf_t	*fdf;
	
	if (argc != 2)
	{
		ft_putstr_fd("Wrong number of arguments", STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
	if (init_fdf(fdf) < 0 || check_map(argv, fdf) < 0)
	{
		ft_putstr_fd(strerror(EXIT_FAILURE), STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
	if ((fdf->mlx = mlx_init(WIDTH, HEIGHT, "FDF", true)) == NULL)
	{
		ft_putstr_fd(mlx_strerror(mlx_errno), STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
	// FDF loop mlx_loop_hook(mlx, ft_hook, mlx);
}