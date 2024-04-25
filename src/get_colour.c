/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colour.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:33:43 by ktoivola          #+#    #+#             */
/*   Updated: 2024/04/25 08:37:07 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int32_t	get_colour(int32_t hex_val)
{
	int32_t colour;

	colour = (hex_val << 24 | hex_val << 16 | hex_val << 8);
	return (colour);
}