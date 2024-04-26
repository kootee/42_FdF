/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:25:33 by ktoivola          #+#    #+#             */
/*   Updated: 2024/04/26 11:26:56 by ktoivola         ###   ########.fr       */
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

static point_t *alloc_map_row(char **pts)
{
	point_t *map_row;
	int		width;
	int 	i;
	
	i = 0;
	width = 0;
	while (pts[width])
		width++;
	ft_printf("width is %i\n", width);
	map_row = malloc(sizeof(point_t) * (width + 1));
	if (!map_row)
		return (NULL);
	while (i < width)
	{
		map_row[i].Z = 0;
		map_row[i].colour = 0;
		map_row[i].last = false;
		i++;
	}
	map_row[i].last = true;
	return (map_row);
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
	
	pts = ft_split(curr_line, ' ');
	map->pt_array[row] = alloc_map_row(pts);
	if (map->pt_array[row] == NULL)
		handle_error(EXIT_FAILURE); //free map points that are mallocd so far   !
	i = 0;
	while (pts[i])
	{
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

int	parse_map_file(int fd, fdf_t *fdf)
{
	char	*line;
	int		row;

	row = 0;
	fdf->map = malloc(sizeof(map_t));
	if (fdf->map == NULL)
		handle_error(EXIT_FAILURE); // don't have to free but should close mlx window as they're mallocd
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
