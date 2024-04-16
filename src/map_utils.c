/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:00:12 by ktoivola          #+#    #+#             */
/*   Updated: 2024/04/16 16:44:22 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	check_map(char **argv, fdf_t *fdf_args)
{
	char	*str;
	int		fd;
	
	if (argv[1] == NULL)
		return (-1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (-1);
	if (parse_fdf_file(fd, fdf_args) < 0)
		return (-1);
	return (0);
}
