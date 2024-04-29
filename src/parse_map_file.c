/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:25:33 by ktoivola          #+#    #+#             */
/*   Updated: 2024/04/29 11:07:23 by ktoivola         ###   ########.fr       */
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
static int alloc_map_row(point_t **map_row, char **pts, int row)
{
	int		width;
	int 	i;
	
	i = 0;
	width = 0;
	while (pts[width])
		width++;
	map_row[row] = malloc(sizeof(point_t) * (width + 1));
	if (!map_row[row])
		return (-1);
	while (i < width)
	{
		map_row[row][i].Z = 0;
		map_row[row][i].colour = 0;
		map_row[row][i].last = false;
		i++;
	}
	map_row[row][i].last = true;
	return (0);
}
void	init_fdf_map(fdf_t *fdf, char **pts, int row)
{
	fdf->map = malloc(sizeof(map_t));
	if (fdf->map == NULL)
		handle_error(EXIT_FAILURE); // don't have to free but should close mlx window as they're mallocd
	fdf->map->pt_array = malloc(sizeof(point_t));
	if (fdf->map->pt_array == NULL)
		handle_error(EXIT_FAILURE);
	if (alloc_map_row(fdf->map->pt_array, pts, row) < 0)
		handle_error_and_free(fdf, EXIT_MAP_ALLOC_FAIL);
}

static void	set_map_points(fdf_t *fdf, map_t *map, char **pts, int row)
{	
	int		i;
	int		j;
	
	/* test */
	// ft_printf("all points of the current line: \n");
	// ft_printf("current line %s\n", curr_line);
	/* --- */
	init_fdf_map(fdf, pts, row); // FDF->MAP gets allocated here
	i = 0;
	while (pts[i])
	{
		j = 0;
		while (pts[i][j] && pts[i][j] != '\n')
		{
			if (!ft_isdigit(pts[i][j]) && !is_hexa_letter(pts[i][j]) 
			&& pts[i][j] != 'x')
				handle_error_and_free(fdf, EXIT_INVALID_MAP);
			if (pts[i][j] == ',')
				map->pt_array[row][i].colour = ft_atoi_base(&pts[i][++j], 16);
			j++;
		}
		map->pt_array[row][i].Z = ft_atoi(pts[i]);
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

int	parse_map_file(int fd, fdf_t *fdf)
{
	char	*line;
	char	**pts;
	int		row;

	row = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		pts = ft_split(line, ' ');
		if (pts == NULL)
			handle_error_and_free(fdf, EXIT_MALLOC_FAIL);
		free(line);
		set_map_points(fdf, fdf->map, pts, row);
		print_map_so_far(row, fdf->map->pt_array);
		row++;
	}
	fdf->map->height = row;
	fdf->map->width = get_map_width(fdf->map);
	free_strs(pts);
	return (0);
}
