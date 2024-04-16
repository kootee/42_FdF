/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fdf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:25:33 by ktoivola          #+#    #+#             */
/*   Updated: 2024/04/16 17:10:19 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_map_width(char *str)
{
	int	i;
	i = 0;
}

void	parse_line(fdf_t *fdf, char *curr_line)
{
	int	i;
	int	j;
	int	width;
	int curr_num;

	i = 0;
	j = 0;
	while (curr_line[i])
	{
		if (curr_line[i] == ft_isalnum(curr_line[i]))
		{
			while (curr_line[i + j] != ' ')
				j++;
			curr_num = (ft_atoi(ft_substr(curr_line, i, j)));
			j = 0;
			add_point(fdf, curr_num, width);
			width++;
		}
		i++;
	}
	fdf->map->width = width;
	
}

void	set_map_points(fdf_t *fdf, int y_coord, char *curr_line)
{	
	int		width;
	int		x_coord;

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

int	parse_fdf_file(int fd, fdf_t *fdf_args)
{
	char *line;
	int	**map_axis;
	int i;

	i = 0;
	map_axis = fdf_args->map->pt_array;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		map_axis[i] = malloc(sizeof(int));
		if (map_axis[i] == NULL)
			return (-1);
		set_map_points(fdf_args, map_axis[i], line);
		fdf_args->map->height++;
	}
	return (0);
}