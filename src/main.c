/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:32:34 by ktoivola          #+#    #+#             */
/*   Updated: 2024/05/13 15:28:17 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_fdf(fdf_t *fdf)
{
	int image_instance_index;
	/* Start mlx */
	fdf->mlx = mlx_init(WIN_X, WIN_Y, "FDF", true); // add function to put name of map
	if (fdf->mlx == NULL)
		handle_error(mlx_errno);
		
	/* Init mlx image */
	fdf->img = mlx_new_image(fdf->mlx, WIN_X, WIN_Y);
	if (fdf->img == NULL)
		handle_error_and_free(fdf, mlx_errno);

	/* Put image to window */
	image_instance_index = mlx_image_to_window(fdf->mlx, fdf->img, 0, 0);
	if (image_instance_index != 0)
		handle_error_and_free(fdf, mlx_errno);
	
	/* Dynamic memory allocation of necessary pointers */
	fdf->camera = NULL;
	fdf->mouse = NULL;
	fdf->win = fdf->mlx->window;
}

void	draw_line(fdf_t *fdf)
{
	int i = 0;
	
	ft_printf("pressed space \n");
	while(i < fdf->mlx->width && i < fdf->mlx->height)
	{
		// mlx_put_pixel(fdf->img, 0 + i, 0 + i, 255);
		ft_putpixel(fdf->img, 0 + i, 0 + i, MAGENTA);
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
int	main(int argc, char **argv)
{
	fdf_t	fdf;
	int i  = 0;
	if (argc != 2) 
		handle_error(EXIT_CMD_COUNT_ERROR);
	if (load_map(argv[1], &fdf.map) > 0)
		handle_error(EXIT_INVALID_MAP);
	while (i < fdf.map.len)
    {
        printf("pt id is %d and stored values X: %0.4f Y: %0.4f Z: %0.4f\n", i, fdf.map.pt_array[i].axis[X], fdf.map.pt_array[i].axis[Y], fdf.map.pt_array[i].axis[Z]);
        printf("\n");
        i++;
    }
	print_pts(fdf.map.pt_array, &fdf.map);
	init_fdf(&fdf);
	draw_map(&fdf);
	/* Error check */
	mlx_loop_hook(fdf.mlx, ft_hook, &fdf);
	mlx_loop(fdf.mlx);
	mlx_terminate(fdf.mlx);
	return (EXIT_SUCCESS);
}