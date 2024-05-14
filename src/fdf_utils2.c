/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:05:25 by ktoivola          #+#    #+#             */
/*   Updated: 2024/05/14 15:44:51 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
/* Str has to be only numbers until, also can't be too big number ',' after that only hexa allowed */
void	validate_point(char *str)
{
	while (*str)
	{
		if (ft_isalnum(*str) == 0)
			handle_error(EXIT_INVALID_MAP);
		str++;
	}
}