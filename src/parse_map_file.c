/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:25:33 by ktoivola          #+#    #+#             */
/*   Updated: 2024/05/14 14:09:11 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	add_points(char *line, map_t *map, int line_number)
{
	int			i;
	char		**pts;
	static int	idx = 0;
	
	pts = ft_split(line, ' ');
	if (pts == NULL)
		return (EXIT_MALLOC_FAIL);
	i = 0;
	while (pts[i] && pts[i][0] != '\n')
	{
/* 		if (!valid_point(&splited[i][0]))
			terminate(ERR_EMPTY); IMPLEMENT */
		map->pt_array[idx].axis[Z] = ft_atoi(pts[i]);
		map->pt_array[idx].axis[X] = i - map->dim.axis[X] / 2;
		map->pt_array[idx].axis[Y] = line_number - map->dim.axis[Y] / 2;
		if (ft_strchr(pts[i], ','))
			map->pt_array[idx].hex_color = set_hexcolor(pts[i]);
		if (map->dim.axis[Z] < map->pt_array[idx].axis[Z])
			map->dim.axis[Z] = map->pt_array[idx].axis[Z];
		if (map->pt_array[idx].axis[Z] < map->min_Z)
			map->min_Z = map->pt_array[idx].axis[Z];
		i++;
		idx++;
	}
	free_strs(pts);
	return (EXIT_SUCCESS);
}

static int	set_map_points(map_t *map)
{
	int			i;
	char		*line;
	char		*remainder;
	static int	line_count;
	
	remainder = map->map_data;
	i = 0;
	line_count = 0;
	line = NULL;
	while (++i)
	{
		if (map->map_data[i] == '\n' || map->map_data[i] == '\0')
		{
			line = ft_substr(remainder, 0, (&map->map_data[i] - remainder));
			if (line == NULL)
				return (EXIT_MALLOC_FAIL);
			remainder = &map->map_data[i + 1];
			if (add_points(line, map, line_count++) > 0) 
				return (EXIT_MALLOC_FAIL);
			free(line);
		}
		if (map->map_data[i] == '\0')
			break ;
	}
	return (EXIT_SUCCESS);
}

static int	set_map_dimensions(map_t *map)
{
	int	pt_count;
	int	i;

	i = 0;
	pt_count = 0;
	while(map->map_data[i])
	{
		if (map->map_data[i] == '\n' && map->map_data[i + 1] == '\0')
			break ;
		if (ft_isalnum(map->map_data[i]) && (map->map_data[i + 1] == '\0' \
			|| map->map_data[i + 1] == ' ' || map->map_data[i + 1] == '\n'))
			pt_count++;
		if	(map->map_data[i++] == '\n')
		{
			if (++map->dim.axis[Y] && map->dim.axis[X] == 0)
				map->dim.axis[X] = pt_count;
			if (pt_count != map->dim.axis[X])
				return (EXIT_FAILURE);
			pt_count = 0;
		}
	}
	if (pt_count != 0 && pt_count != map->dim.axis[X])
		return (EXIT_FAILURE);
	map->dim.axis[Y]++;
	return (0);
}
static char *read_map_data(int fd)
{
	char	*line;
	char	*map_data;
	char	*temp_to_free;
	
	map_data = ft_calloc(1, sizeof(char));
	if (map_data == NULL)
		handle_error(EXIT_MALLOC_FAIL);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		temp_to_free = map_data;
		map_data = ft_strjoin(map_data, line);
		if (map_data == NULL)
		{
			free(line);
			free(temp_to_free);
			handle_error(EXIT_MALLOC_FAIL);		
		}
		free(temp_to_free);
		free(line);
	}
	return (map_data);
}

void	load_map(char *map_file_path, map_t *map)
{
	int		fd;

	init_map(map);
	fd = open(map_file_path, O_RDONLY);
	if (fd < 0)
		handle_error(mlx_errno);
	map->map_data = read_map_data(fd);
	if (set_map_dimensions(map) > 0)
		handle_map_error(map);
	map->len = map->dim.axis[X] * map->dim.axis[Y];
	map->pt_array = ft_calloc(map->len, sizeof(point_t));
	if (map->pt_array == NULL)
		handle_map_error(map);
	if (set_map_points(map) > 0)
	{
		free(map->pt_array);
		handle_map_error(map);
	}
	set_point_colors(map, map->pt_array, map->colors, map->len);
	close(fd);
}
