/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:25:33 by ktoivola          #+#    #+#             */
/*   Updated: 2024/04/23 16:10:35 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	open_map(char *str)
{
	int		fd;
	
	if (str == NULL)
		return (-1);
	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (-1);
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

static point_t *alloc_map_row(int width)
{
	int 	i;
	point_t *map_row;
	
	i = 0;
	map_row = malloc(sizeof(point_t) * width);
	if (!map_row)
		handle_error(EXIT_FAILURE); // handle error properly
	while (width--)
	{
		map_row[i].Z = 0;
		map_row[i].colour = 0;
	}
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
	int		x_coord;
	int		i;
	
	x_coord = 0;
	while (*curr_line)
	{
		i = 0;
		while (*curr_line && *curr_line == ' ')
			*curr_line++;
		while (*curr_line && ft_isalnum(*curr_line))
		{
			if (*curr_line == ',')
			{
				row[x_coord].colour = get_colour((int16_t)ft_atoi_base(*(curr_line + 1), 16));
				curr_line = *(curr_line + 3);
			}
			i++;
		}
		row[x_coord++].Z = ft_atoi(ft_substr(curr_line, 0, i));
		curr_line = *(curr_line + i);
	}
	return (0);
}


int	parse_map_file(char *str, t_fdf *fdf)
{
	point_t	**map_grid;
	char	*line;
	int		row;
	int		fd;

	row = 0;
	fd = open_map(str);
	if (fd < 0)
		handle_error(strerror(mlx_errno));
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		map_grid[row] = alloc_map_row(get_row_len(line));
		if (map_grid[row] == NULL)
			handle_error(EXIT_FAILURE);
		if (set_map_points(map_grid[row], line) < 0)
			handle_error(EXIT_FAILURE);
		row++;
	}
	fdf->map->pt_array = map_grid;
	fdf->map->height = row;
	return (0);
}
