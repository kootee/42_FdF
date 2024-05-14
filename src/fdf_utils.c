/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 12:33:16 by ktoivola          #+#    #+#             */
/*   Updated: 2024/05/14 14:52:15 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int32_t	set_hexcolor(char *str)
{
	int32_t color;
	
	while(*str != ',')
		str++;
	color = ft_atoi_base(str + 2, 16);
	return (color);
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

int	round_to_int(double n)
{
	int	rounded;

	rounded = (int)n;
	if (n - rounded >= 0.5)
		rounded++;
	return (rounded);
}
