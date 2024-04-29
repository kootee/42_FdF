/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:32:34 by ktoivola          #+#    #+#             */
/*   Updated: 2024/04/29 14:29:38 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_fdf(fdf_t *fdf)
{
	/* Start mlx */
	fdf->mlx = mlx_init(WIDTH, HEIGHT, "FDF", true); // add function to put name of map
	if (fdf->mlx == NULL)
		handle_error(mlx_errno);
		
	/* Init mlx image */
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	if (fdf->img == NULL)
		handle_error_and_free(fdf, mlx_errno);

	/* Put image to window */
	if (mlx_image_to_window(fdf->mlx, fdf->img, 0, 0) < 0)
		handle_error_and_free(fdf, mlx_errno);
	
	/* Dynamic memory allocation of necessary pointers */
	fdf->win = NULL;
	fdf->camera = NULL;
	fdf->mouse = NULL;
	fdf->map = malloc(sizeof(map_t));
	if (fdf->map == NULL)
		handle_error(EXIT_FAILURE); // don't have to free should close mlx window as they're mallocd
}

void	draw_line(fdf_t *fdf)
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
	fdf_t *fdf;
	mlx_t *mlx_inst;
	fdf = param; // is it not possible to use param straight?
	mlx_inst = fdf->mlx;
 	if (mlx_is_key_down(fdf->mlx, MLX_KEY_SPACE))
		draw_line(fdf);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_1))
		ft_printf("width is %i\n", mlx_inst->width);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(fdf->mlx);
}
/* add above to fdf.c file */
int32_t	main(int argc, char **argv)
{
	fdf_t	fdf;
	int		fd;

	if (argc != 2) 
		handle_error(EXIT_CMD_COUNT_ERROR);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		handle_error(mlx_errno);
	init_fdf(&fdf);
	parse_map_file(fd, &fdf);
	
	mlx_loop_hook(fdf.mlx, ft_hook, &fdf);
	mlx_loop(fdf.mlx);
	
	mlx_terminate(fdf.mlx);
	return (EXIT_SUCCESS);
}