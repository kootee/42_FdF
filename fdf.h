/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:11:53 by ktoivola          #+#    #+#             */
/*   Updated: 2024/04/11 11:13:26 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct  mlx 
{
    void    *window;
    void    *context;
    int32_t width;
    int32_t height;
    double  delta_time;    
}               mlx_t;