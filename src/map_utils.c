/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:00:12 by ktoivola          #+#    #+#             */
/*   Updated: 2024/04/15 15:13:49 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	check_map(char **argv, fdf_t *fdf_args)
{
	char	*s_ptr;
	int		fd;
	
	if (argv[1] == NULL)
		return (-1);
	s_ptr = ft_strncmp(argv[1], ".fdf", ft_strlen(argv[1]));
	if (ft_strncmp(s_ptr, *(argv[1] - 3), 4) == NULL)
		return (-1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (-1);
	parse_fdf(fd, fdf_args);
}
