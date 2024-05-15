/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:05:25 by ktoivola          #+#    #+#             */
/*   Updated: 2024/05/15 09:43:59 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
/* Str has to be only numbers until, also can't be too big number ',' after that only hexa allowed */
void	validate_point(char *str, map_t *map)
{
	while (*str)
	{
		if (ft_isalnum(*str) || *str == ',' || *str == '\n' || *str == '-')
		{
			if (*str > 'G' && *str < 'Z')	
				handle_map_error(map);
		}
		else
			handle_map_error(map);
		str++;
	}
}