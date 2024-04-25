/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:32:34 by ktoivola          #+#    #+#             */
/*   Updated: 2024/04/25 11:58:21 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_fdf(t_fdf *fdf)
{
	/* Start mlx */
	fdf->mlx = mlx_init(WIDTH, HEIGHT, "FDF", true);
	if (fdf->mlx == NULL)
		handle_error(mlx_errno);
		
	/* Init mlx image */
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	if (fdf->img == NULL)
		handle_img_error(mlx_strerror(mlx_errno), fdf);

	if (mlx_image_to_window(fdf->mlx, fdf->img, 0, 0) < 0)
		handle_img_error(mlx_strerror(mlx_errno), fdf);
}

static void	close_fdf(t_fdf *fdf)
{
	mlx_delete_image(fdf->mlx, fdf->img);
	mlx_terminate(fdf->mlx);
}

void	draw_line(t_fdf *fdf)
{
	int i = 0;
	mlx_t *mlx_inst = fdf->mlx;
	ft_printf("pressed space \n");
	while(i < mlx_inst->width && i < mlx_inst->height)
	{
		mlx_put_pixel(fdf->img, 0 + i, 0 + i, 255);
		i++;
	}
}

void	ft_hook(void *param)
{
	t_fdf *fdf;
	mlx_t *mlx_inst;
	fdf = param; // is it not possible to use param straight?
	mlx_inst = fdf->mlx;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_SPACE))
		draw_line(fdf);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_1))
		printf("width is %i\n", mlx_inst->width);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(fdf->mlx);
}

int32_t	main(int argc, char **argv)
{
	t_fdf	fdf;
	int	fd;

	if (argc != 2)
	{
		ft_printf("nothing to see here\n");
		// handle_error(strerror(EXIT_FAILURE)); // add errnos
	}
	init_fdf(&fdf);
	fd = open(argv[1], O_RDONLY);
	ft_printf("path is %s\n", argv[1]);
	ft_printf("fd is %i\n", fd);
	if (fd < 0)
		handle_error(mlx_errno);
	// parse_map_file(fd, fdf);
	
	mlx_loop_hook(fdf.mlx, ft_hook, &fdf);
		
	mlx_loop(fdf.mlx);
	close_fdf(&fdf);
	return (EXIT_SUCCESS);
	// FDF loop mlx_loop_hook(mlx, ft_hook, mlx);
}