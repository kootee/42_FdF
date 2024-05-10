/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:25:33 by ktoivola          #+#    #+#             */
/*   Updated: 2024/05/10 12:51:05 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	init_map(map_t *map)
{
	map->dim.axis[X] = 0;
	map->dim.axis[Y] = 0;
	map->dim.axis[Z] = 0;
	map->origo.axis[X] = WIN_X / 2;
	map->origo.axis[Y] = WIN_Y / 2;
	map->origo.axis[Y] = 0;
	map->len = 0;
	map->map_data = NULL;
	map->pt_array = NULL;
	map->min_Z = INT32_MAX;
	map->scale = 1;
	init_colors(map);
}
char *read_map_data(int fd)
{
	char	*line;
	char	*map_data;
	char	*temp_to_free;
	
	map_data = ft_calloc(1, sizeof(char)); // protect malloc
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		temp_to_free = map_data;
		map_data = ft_strjoin(map_data, line);		
		free(temp_to_free);
	}
	free(line);	
	return (map_data);
}
void	set_map_dimensions(map_t *map)
{
	int	pt_count;
	int	i;

	i = 0;
	pt_count = 0;
	while(map->map_data[i])
	{
		ft_printf("i is %d and char is %c\n", i, map->map_data[i]);
		if (map->map_data[i] == '\n' && map->map_data[i + 1] == '\0')
			break ;
		if (ft_isalnum(map->map_data[i]) && (map->map_data[i + 1] == '\0' \
			|| map->map_data[i + 1] == ' ' || map->map_data[i + 1] == '\n'))
		{
			pt_count++; // is a valid input and next one is a space or newline add to the counter of elements
			ft_printf("pt count is %d\n", pt_count);	
		}
		if	(map->map_data[i] == '\n')
		{
			map->dim.axis[Y]++;
			if (map->dim.axis[X] == 0)
				map->dim.axis[X] = pt_count;
			if (pt_count != map->dim.axis[X])
				handle_error(EXIT_FAILURE);
			pt_count = 0;
		}
		i++;
	}
	if (pt_count != 0 && pt_count != map->dim.axis[X])
		handle_error(EXIT_FAILURE); // handle map error
	map->dim.axis[Y]++;
}

void	add_points(char *line, map_t *map, int line_number)
{
	int			i;
	char		**pts;
	static int	idx = 0;
	
	pts = ft_split(line, ' '); // malloc protect
	i = 0;
	while (pts[i] && pts[i][0] != '\n')
	{
/* 		if (!valid_point(&splited[i][0]))
			terminate(ERR_EMPTY); IMPLEMENT */
		map->pt_array[idx].axis[Z] = ft_atoi(pts[i]);
		map->pt_array[idx].axis[X] = i - map->dim.axis[X] / 2;
		map->pt_array[idx].axis[Y] = line_number - map->dim.axis[Y] / 2;
		map->pt_array[idx].color = DEFAULT_COLOR;
		if (ft_strchr(pts[i], ','))
			map->pt_array[idx].hex_color = set_hexcolor(pts[i]);
		if (map->dim.axis[Z] < map->pt_array[idx].axis[Z])
			map->dim.axis[Z] = map->pt_array[idx].axis[Z];
		if (map->pt_array[idx].axis[Z] < map->min_Z)
			map->min_Z = map->pt_array[idx].axis[Z];
		// need to check the other values?
		printf("pt id is %d and stored values X: %0.4f Y: %0.4f Z: %0.4f\n", idx, map->pt_array[idx].axis[X], map->pt_array[idx].axis[Y], map->pt_array[idx].axis[Z]);
		fflush(stdout);
		i++;
		idx++;
	}
	printf("\n");
	free_strs(pts);
}

void	set_map_points(map_t *map)
{
	int			i;
	char		*line;
	char		*remainder;
	static int	line_count;
	// static int	points_count;
	
	line = NULL;
	remainder = map->map_data;
	map->pt_array = ft_calloc(map->len, sizeof(point_t));
	i = 0;
	line_count = 0;
	while (++i)
	{
		if (map->map_data[i] == '\n' || map->map_data[i] == '\0')
		{
			line = ft_substr(remainder, 0, \
							(&map->map_data[i] - remainder));
			ft_printf("line is %s\n", line);
			remainder = &map->map_data[i + 1];
			add_points(line, map, line_count++);
			free(line);
		}
		if (map->map_data[i] == '\0')
			break ;
	}
	//free(line);
}

int	load_map(char *map_file_path, map_t *map)
{
	int		fd;

	init_map(map);
	fd = open(map_file_path, O_RDONLY);
	if (fd < 0)
		handle_error(mlx_errno);
	map->map_data = read_map_data(fd); // error check
	set_map_dimensions(map);
	map->len = map->dim.axis[X] * map->dim.axis[Y];
	set_map_points(map);
	set_point_colors(map, map->pt_array, map->colors, map->len);
	close(fd);
	return (0);
}
