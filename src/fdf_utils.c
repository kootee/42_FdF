/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 12:33:16 by ktoivola          #+#    #+#             */
/*   Updated: 2024/04/29 13:50:31 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int32_t	get_colour(int32_t hex_val)
{
	int32_t colour;

	colour = (hex_val << 24 | hex_val << 16 | hex_val << 8);
	return (colour);
}

bool	is_hexa_letter(char c)
{
	if ((c >= 'A' && c <= 'F')
	|| (c >= 'a' && c <= 'f'))
		return (true);
	return (false);
}

void	free_map_pts(point_t **pts)
{
	while(pts)
	{
		free(*pts);
		pts++;
	}
	free(pts);
}

void	free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}
