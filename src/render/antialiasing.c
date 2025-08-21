/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:35:10 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/21 12:39:50 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_clr	get_avr(int pcoo[2], const t_img img)
{
	const t_clr	*base_pxl = img.p_data[pcoo[X] + pcoo[Y] * img.width];
	uint64_t	sum[3];
	uint64_t	coef[3];

	sum[R] = 
}

void	antialiasing(t_render *render)
{

}
