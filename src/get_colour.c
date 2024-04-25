/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colour.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:33:43 by ktoivola          #+#    #+#             */
/*   Updated: 2024/04/23 15:50:30 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int16_t	get_colour(int16_t hex_val)
{
	int16_t colour;

	colour = (hex_val << 24 | hex_val << 16 | hex_val << 8);
	return (colour);
}