/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:32:34 by ktoivola          #+#    #+#             */
/*   Updated: 2024/04/23 16:03:01 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_fdf(t_fdf *fdf)
{
	/* Start mlx */
	fdf->mlx = mlx_init(WIDTH, HEIGHT, "FDF", true);
	if (fdf->mlx == NULL)
		handle_error(mlx_strerror(mlx_errno));
		
	/* Init mlx image */
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	if (fdf->img == NULL)
		handle_img_error(mlx_strerror(mlx_errno), fdf);

	/* Extra */
	mlx_texture_t *texture = mlx_load_png("./images/pixil-frame-0.png");
	if (texture == NULL)
		exit (1);
	fdf->img = mlx_texture_to_image(fdf->mlx, texture);
	if (!fdf->img)
		exit (1);
	mlx_delete_texture(texture);
	if (mlx_image_to_window(fdf->mlx, fdf->img, 0, 0) < 0)
		handle_img_error(mlx_strerror(mlx_errno), fdf);
}

static void	close_fdf(t_fdf *fdf)
{
	mlx_delete_image(fdf->mlx, fdf->img);
	mlx_terminate(fdf->mlx);
}

void	ft_hook(void *param)
{
	mlx_t *fdf;
	
	fdf = param; // is it not possible to use param straight?
	if (mlx_is_key_down(fdf, MLX_KEY_ESCAPE))
		mlx_close_window(fdf);
}

int32_t	main(int argc, char **argv)
{
	t_fdf	*fdf;

	if (argc != 2)
	{
		ft_printf("nothing to see here\n");
		// handle_error(strerror(EXIT_FAILURE)); // add errnos
	}
	fdf = malloc(sizeof(t_fdf));
	if (fdf == NULL)
		handle_error(mlx_strerror(mlx_errno));
	init_fdf(fdf);
	parse_map_file(argv[1], fdf);
	
	mlx_loop_hook(fdf->mlx, ft_hook, fdf->mlx);
		
	mlx_loop(fdf->mlx);
	close_fdf(fdf);
	return (EXIT_SUCCESS);
	// FDF loop mlx_loop_hook(mlx, ft_hook, mlx);
}