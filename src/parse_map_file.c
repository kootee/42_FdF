/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:25:33 by ktoivola          #+#    #+#             */
/*   Updated: 2024/04/26 12:20:20 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

bool	is_hexa_letter(char c)
{
	if ((c >= 'A' && c <= 'F')
	|| (c >= 'a' && c <= 'f'))
		return (true);
	return (false);
}

static void alloc_map_row(point_t **map_row, char **pts, int row)
{
	int		width;
	int 	i;
	
	i = 0;
	width = 0;
	while (pts[width])
		width++;
	ft_printf("width is %i\n", width);
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

/* void	parse_line(t_fdf *fdf, char *curr_line)
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
	
} */

static void	set_map_points(map_t *map, int row, char *curr_line)
{	
	char 	**pts;
	int		i;
	int		j;
	// have a function print out a map each time
	pts = ft_split(curr_line, ' ');
	alloc_map_row(map->pt_array, pts, row);
	if (map->pt_array[row] == NULL)
		handle_error(EXIT_FAILURE); //free map points that are mallocd so far   !
	i = 0;
	while (pts[i])
	{
		ft_printf("number is %s and index is %d\n", pts[i], i);
		j = 0;
		while (pts[i][j] && (ft_isdigit(pts[i][j]) || is_hexa_letter(pts[i][j]) 
			|| pts[i][j] == 'x'))
		{
			if (pts[i][j] == ',')
				map->pt_array[row][i].colour = 
				get_colour(ft_atoi_base(&pts[i][++j], 16));
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
void	init_fdf_map(fdf_t *fdf)
{
	fdf->map = malloc(sizeof(map_t)); // init map func instead
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
		row++;
	}
	fdf->map->height = row; // what to do with this
	fdf->map->width = get_map_width(fdf->map);
	return (0);
}
