/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:25:33 by ktoivola          #+#    #+#             */
/*   Updated: 2024/04/25 11:04:25 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_row_len(char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (!ft_isalnum(*str))
			return (-1); // could be more elaborate
		while (*str && *str == ' ')
			str++;
		while (*str && (ft_isdigit(*str) || is_hexa_letter(*str) 
			|| *str == 'x'))
			str++;
		count++;
	}
	return (count);
}

static point_t *alloc_map_row(int width)
{
	int 	i;
	point_t *map_row;
	
	if (width == -1)
		return (NULL);
	i = 0;
	map_row = malloc(sizeof(point_t) * width);
	if (!map_row)
		return (NULL);
	while (i < width)
	{
		map_row[i].Z = 0;
		map_row[i].colour = 0;
		i++;
	}
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

static void	set_map_points(point_t *row, char *curr_line)
{	
	char 	**pts;
	int		x;
	int		i;
	
	x = 0;
	pts = ft_split(curr_line, ' ');
	while (pts[x])
	{
		i = 0;
		while (pts[x][i] && (ft_isdigit(pts[x][i]) 
			|| is_hexa_letter(pts[x][i]) 
			|| pts[x][i] == 'x'))
		{
			if (pts[x][i] == ',')
				row[x].colour = get_colour(ft_atoi_base(&pts[x][++i], 16));
			i++;
		}
		row[x].Z = ft_atoi(pts[x]);
		x++;
	}
}

int	parse_map_file(int fd, t_fdf *fdf)
{
	point_t	**map_grid;
	char	*line;
	int		row;

	row = 0;
	map_grid = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		map_grid[row] = alloc_map_row(get_row_len(line));
		if (map_grid[row] == NULL)
			handle_error(EXIT_FAILURE); // error parsing map
		set_map_points(map_grid[row++], line);
	}
	fdf->map->pt_array = map_grid;
	fdf->map->height = row;
	return (0);
}
