/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:32:34 by ktoivola          #+#    #+#             */
/*   Updated: 2024/05/17 13:36:21 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_fdf(t_fdf *fdf)
{
	fdf->mlx = mlx_init(WIN_X, WIN_Y, "FDF", true);
	if (fdf->mlx == NULL)
		handle_error(&fdf->map, mlx_errno);
	fdf->img = mlx_new_image(fdf->mlx, WIN_X, WIN_Y);
	if (fdf->img == NULL)
		error_terminate_mlx(fdf, mlx_errno);
	if (mlx_image_to_window(fdf->mlx, fdf->img, 0, 0) < 0)
		error_terminate_mlx(fdf, mlx_errno);
}

static void	ft_hook(void *param)
{
	t_fdf	*fdf;
	mlx_t	*mlx_inst;

	fdf = param;
	mlx_inst = fdf->mlx;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(fdf->mlx);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;
	t_point	*map_projection;

	if (argc != 2)
		handle_error(NULL, EXIT_CMD_COUNT_ERROR);
	load_map(argv[1], &fdf.map);
	init_fdf(&fdf);
	map_projection = ft_calloc(fdf.map.len, sizeof(t_point));
	draw_map(&fdf, map_projection);
	mlx_loop_hook(fdf.mlx, ft_hook, &fdf);
	mlx_loop(fdf.mlx);
	free(fdf.map.pt_array);
	free(map_projection);
	mlx_terminate(fdf.mlx);
	return (EXIT_SUCCESS);
}
