/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:25:33 by ktoivola          #+#    #+#             */
/*   Updated: 2024/04/27 14:15:46 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* test functions - remove before evaluation */
void	print_map_so_far(int row, point_t **map)
{
	int	i = 0;

	ft_printf("ROW %d: [", row);
	while (!(map[row][i].last))
	{
		ft_printf("%i	", map[row][i].Z);
		if (map[row][i].last == true)
			ft_printf(".");
		i++;
	}
	ft_printf("]\n");
}
/* --- */
static void alloc_map_row(point_t **map_row, char **pts, int row)
{
	int		width;
	int 	i;
	
	i = 0;
	width = 0;
	while (pts[width])
		width++;
	// ft_printf("width is %i\n", width);
	map_row[row] = malloc(sizeof(point_t) * (width + 1));
	if (!map_row[row])
		handle_error(EXIT_FAILURE);
	while (i < width)
	{
		map_row[row][i].Z = 0;
		map_row[row][i].colour = 0;
		map_row[row][i].last = false;
		i++;
	}
	map_row[row][i].last = true;
}

static void	set_map_points(map_t *map, int row, char *curr_line)
{	
	char 	**pts;
	int		i;
	int		j;
	// have a function print out the map each time
	pts = ft_split(curr_line, ' ');
	/* test */
	// ft_printf("all points of the current line: \n");
	// ft_printf("current line %s\n", curr_line);
	/* --- */
	alloc_map_row(map->pt_array, pts, row);
	if (map->pt_array[row] == NULL)
		handle_error(EXIT_FAILURE); //free map points that are mallocd so far   !
	i = 0;
	while (pts[i])
	{
		// ft_printf("[%s] index: %d\n", pts[i], i);
		j = 0;
		while (pts[i][j] && pts[i][j] != '\n')
		{
			if (!ft_isdigit(pts[i][j]) && !is_hexa_letter(pts[i][j]) 
			&& pts[i][j] != 'x')
				handle_error(EXIT_FAILURE);
			if (pts[i][j] == ',')
				map->pt_array[row][i].colour = ft_atoi_base(&pts[i][++j], 16);
			j++;
		}
		map->pt_array[row][i].Z = ft_atoi(pts[i]);
		// ft_printf("should store %i\n", ft_atoi(pts[i]));
		// ft_printf("%i was stored\n", map->pt_array[row][i].Z);
		i++;
	}
}

int	get_map_width(map_t *map)
{
	int	i;
	int	width;
	int comp;
	
	i = 0;
	comp = 0;
	while (i < map->height)
	{
		width = 0;
		while (!map->pt_array[i][width].last)
			width++;
		if (width > comp)
			comp = width;
		i++;
	}
	return (comp);
}
void	init_fdf_map(fdf_t *fdf)
{
	fdf->map = malloc(sizeof(map_t));
	if (fdf->map == NULL)
		handle_error(EXIT_FAILURE); // don't have to free but should close mlx window as they're mallocd
	fdf->map->pt_array = malloc(sizeof(point_t));
	if (fdf->map->pt_array == NULL)
		handle_error(EXIT_FAILURE);
}

int	parse_map_file(int fd, fdf_t *fdf)
{
	char	*line;
	int		row;

	row = 0;
	init_fdf_map(fdf);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		set_map_points(fdf->map, row, line);
		print_map_so_far(row, fdf->map->pt_array);
		row++;
	}
	fdf->map->height = row; // what to do with this
	fdf->map->width = get_map_width(fdf->map);
	return (0);
}
