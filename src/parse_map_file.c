/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:25:33 by ktoivola          #+#    #+#             */
/*   Updated: 2024/04/29 16:06:51 by ktoivola         ###   ########.fr       */
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

/* int	get_map_width(map_t *map)
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
} */

int	get_row_width(char **pts)
{
	int	width;

	width = 0;
	while (pts[width])
		width++;
	ft_printf("width: %d\n", width);
	return (width);
}

static int alloc_map_row(map_t *map, int row, int width)
{
	int 	i;
	
	map->pt_array = malloc(sizeof(point_t)); 
	if (map->pt_array == NULL)
		handle_error(EXIT_FAILURE);
	map->pt_array[row] = malloc(sizeof(point_t) * (width + 1));
	if (map->pt_array[row])
		return (-1);
	i = 0;
	while (i < width)
	{
		map->pt_array[row][i].Z = 0;
		map->pt_array[row][i].colour = 0;
		map->pt_array[row][i].last = false;
		i++;
	}
	map->pt_array[row][i].last = true;
	ft_printf("alloced row %d of width %d\n", row, width);
	return (0);
}

static void	set_map_points(map_t *map, char **pts, int row)
{	
	int		i;
	int		j;
	
	
	i = 0;
	ft_printf("pts are: ");
	while (pts[i])
	{
		ft_printf(" %s ", pts[i]);
		i++;
	}
	ft_printf("\n");
	
	i = 0;
	while (pts[i])
	{
		j = 0;
		// ft_printf("i is %d and value is %s\n", i, pts[i]);
		while (pts[i][j] != '\0' && pts[i][j] != '\n')
		{
			// ft_printf("j is %d and char is %c\n", j, pts[i][j]);
			if (!ft_isdigit(pts[i][j]) && !is_hexa_letter(pts[i][j]) 
			&& pts[i][j] != 'x')
				handle_error(EXIT_INVALID_MAP);
			if (pts[i][j] == ',')
				map->pt_array[row][i].colour = ft_atoi_base(&pts[i][++j], 16);
			j++;
		}
		map->pt_array[row][i].Z = ft_atoi(pts[i]);
		i++;
	}
	ft_printf("map points set, returning\n");
}

void	init_map(map_t *map)
{
	map->height = 0;
	map->width = 0;
	map->pt_array = NULL;
}

int	load_map(int fd, map_t *map)
{
	char	*line;
	char	**pts;
	int		row;

	row = 0;
	init_map(map);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		pts = ft_split(line, ' ');
		if (pts == NULL)
			handle_error(EXIT_MALLOC_FAIL);
		alloc_map_row(map, row, get_row_width(pts)); 
		set_map_points(map, pts, row);
		print_map_so_far(row, map->pt_array);
		row++;
	}
	map->height = row;
	map->width = get_row_width(pts);
	free(line);
	free_strs(pts);
	return (0);
}
