/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:25:33 by ktoivola          #+#    #+#             */
/*   Updated: 2024/05/21 13:30:34 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	add_points(char *line, t_map *map, int line_number)
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
		validate_point(pts[i], map);
		map->pt_array[idx].axis[Z] = ft_atoi(pts[i]);
		map->pt_array[idx].axis[X] = i - map->dim.axis[X] / 2;
		map->pt_array[idx].axis[Y] = line_number - map->dim.axis[Y] / 2;
		if (ft_strchr(pts[i], ','))
			map->pt_array[idx].hex_color = set_hexcolor(pts[i]);
		set_z_values(map, idx);
		i++;
		idx++;
	}
	if (i != map->dim.axis[X] && line_number != map->dim.axis[Y])
		set_uneven(++idx, line_number, map);
	free_strs(pts);
	return (EXIT_SUCCESS);
}

static void	set_map_points(t_map *map)
{
	int			i;
	char		*line;
	char		*remainder;
	static int	line_count;

	remainder = map->map_data;
	i = 0;
	line_count = 0;
	if (map->map_data[i] == '\0')
		handle_error(map, EXIT_INVALID_MAP_PTS);
	while (++i)
	{
		if (map->map_data[i] == '\n' || map->map_data[i] == '\0')
		{
			line = ft_substr(remainder, 0, (&map->map_data[i] - remainder));
			if (line == NULL)
				handle_error(map, EXIT_MALLOC_FAIL);
			remainder = &map->map_data[i + 1];
			if (add_points(line, map, line_count++) > 0)
				handle_error(map, EXIT_MALLOC_FAIL);
			free(line);
		}
		if (map->map_data[i] == '\0')
			break ;
	}
}

static void	set_map_dimensions(t_map *map)
{
	int	pt_count;
	int	i;

	i = -1;
	pt_count = 0;
	while (map->map_data[++i])
	{
		if (map->map_data[i] == '\n' && map->map_data[i + 1] == '\0')
			break ;
		if (ft_isalnum(map->map_data[i]) && (map->map_data[i + 1] == '\0' \
			|| map->map_data[i + 1] == ' ' || map->map_data[i + 1] == '\n'))
			pt_count++;
		if (map->map_data[i] == '\n')
		{
			if (map->dim.axis[X] != 0 && (pt_count > map->dim.axis[X] + 1
				|| pt_count < map->dim.axis[X] - 1))
				handle_error(map, EXIT_INVALID_MAP_DIM);
			map->dim.axis[Y]++;
			map->dim.axis[X] = pt_count;
			pt_count = 0;
		}
	}
	if (map->dim.axis[X] == 0)
		map->dim.axis[X] = pt_count;
	map->dim.axis[Y]++;
}

static char	*read_map_data(t_map *map, int fd)
{
	char	*line;
	char	*map_data;
	char	*temp_to_free;

	map_data = ft_calloc(1, sizeof(char));
	if (map_data == NULL)
		handle_error(map, EXIT_MALLOC_FAIL);
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
			handle_error(map, EXIT_MALLOC_FAIL);
		}
		free(temp_to_free);
		free(line);
	}
	return (map_data);
}

void	load_map(char *map_file_path, t_map *map)
{
	int		fd;

	check_path(map, map_file_path);
	init_map(map);
	fd = open(map_file_path, O_RDONLY);
	if (fd < 0)
		handle_error(map, EXIT_OPEN_ERROR);
	map->map_data = read_map_data(map, fd);
	set_map_dimensions(map);
	map->len = map->dim.axis[X] * map->dim.axis[Y];
	map->pt_array = ft_calloc(map->len, sizeof(t_point));
	if (map->pt_array == NULL)
		handle_error(map, EXIT_MALLOC_FAIL);
	set_map_points(map);
	set_point_colors(map, map->pt_array, map->colors);
	free(map->map_data);
	map->map_data = NULL;
	close(fd);
}
