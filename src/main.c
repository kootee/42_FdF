/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:32:34 by ktoivola          #+#    #+#             */
/*   Updated: 2024/05/15 13:20:07 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_fdf(fdf_t *fdf)
{
	fdf->mlx = mlx_init(WIN_X, WIN_Y, "FDF", true);
	if (fdf->mlx == NULL)
		handle_error(mlx_errno);
	fdf->img = mlx_new_image(fdf->mlx, WIN_X, WIN_Y);
	if (fdf->img == NULL)
		handle_error_terminate_mlx(fdf, mlx_errno);
	if (mlx_image_to_window(fdf->mlx, fdf->img, 0, 0) < 0)
		handle_error_terminate_mlx(fdf, mlx_errno);
}

static void	ft_hook(void *param)
{
	fdf_t	*fdf;
	mlx_t	*mlx_inst;

	fdf = param;
	mlx_inst = fdf->mlx;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(fdf->mlx);
}

int	main(int argc, char **argv)
{
	fdf_t	fdf;

	if (argc != 2)
		handle_error(EXIT_CMD_COUNT_ERROR);
	load_map(argv[1], &fdf.map);
	init_fdf(&fdf);
	draw_map(&fdf);
	mlx_loop_hook(fdf.mlx, ft_hook, &fdf);
	mlx_loop(fdf.mlx);
	free(fdf.map.pt_array);
	mlx_terminate(fdf.mlx);
	return (EXIT_SUCCESS);
}
