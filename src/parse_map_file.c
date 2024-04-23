/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:25:33 by ktoivola          #+#    #+#             */
/*   Updated: 2024/04/23 13:57:14 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	open_map(char *str, t_fdf *fdf_args)
{
	int		fd;
	
	if (str == NULL)
		handle_error(mlx_strerror(mlx_errno));
	fd = open(str, O_RDONLY);
	if (fd < 0)
		handle_error(mlx_strerror(mlx_errno));
	return (fd);
}

int	get_row_len(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (*str)
	{
		if (!ft_isalnum(*str))
			return (-1);
		while (*str && *str == ' ')
			*str++;
		while (*str && ft_isalnum(*str))
			*str++;
		count++;
	}
	return (count);
}

void	parse_line(t_fdf *fdf, char *curr_line)
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

static int	set_map_points(point_t *row, char *curr_line)
{	
	// char	*map_data;
	int		x_coord;
	int		i;
	
	x_coord = 0;
	while (*curr_line)
	{
		i = 0;
	/* 	if (!ft_isalnum(*curr_line)) // is it necessary?
			return (-1); */
		while (*curr_line && *curr_line == ' ')
			*curr_line++;
		while (*curr_line && ft_isalnum(*curr_line))
		{
			if (*curr_line == ',')
			{
				row[x_coord].colour = set_colour(*(curr_line));
				curr_line = *(curr_line + 3);
			}
			i++;
		}
		row[x_coord++].Z = ft_atoi(ft_substr(curr_line, 0, i));
		curr_line = *(curr_line + i);
	}
	return (0);
}

void	alloc_map(point_t *map, int width)
{
	int i;
	
	i = 0;
	map = malloc(sizeof(point_t) * width);
	while (width--)
	{
		map[i].Z = 0;
		map[i].colour = 0;
	}
}

int	parse_map_file(char *str, t_fdf *fdf)
{
	point_t	**map_grid;
	char	*line;
	int		fd;
	int		row;

	row = 0;
	fd = open_map(str, fdf);
	line = get_next_line(fd);
	fdf->map->width = get_row_len(line);
	while (line)
	{
		map_grid[row] = malloc(sizeof(point_t) * fdf->map->width); // CHANGE THIS TO ALLOC AND SET TO ZERO & Colours allocs a new ROW
		if (map_grid[row] == NULL)
			handle_error(EXIT_FAILURE);
		if (set_map_points(map_grid[row], line) < 0)
			handle_error(EXIT_FAILURE);
		row++;
		line = get_next_line(fd);
	}
	fdf->map->pt_array = map_grid;
	fdf->map->height = row;
	return (0);
}
