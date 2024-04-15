/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fdf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:25:33 by ktoivola          #+#    #+#             */
/*   Updated: 2024/04/15 16:34:52 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_map_width(char *str)
{
	int	i;

	i = 0;
}
void	set_map_points(fdf_t *fdf, int y_coord, char *str)
{	
	int		width;
	int		x_coord;
	char	**curr_line;

	curr_line = ft_split(str, ' '); // deal with missing points
	width = get_map_width(curr_line);
	if (width == 0)
		exit (EXIT_FAILURE);
	fdf->map[y_coord] = malloc(sizeof(int) * width + 1);
	while (*str)
	{
		if (*str != )
	}
}

int	parse_fdf(int fd, fdf_t *fdf_args)
{
	char *line;
	int	y_coord;

	y_coord = 0;
	line = get_next_line(fd);
	while (line)
	{
		fdf_args->map[y_coord] = malloc(sizeof(int));
		if (fdf_args->map[y_coord])
			return (-1);
		set_map_points(fdf_args, y_coord, line);
		line = get_next_line(fd);
		y_coord++;
		// check for errors
	}
	return (0);
}