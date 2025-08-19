/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_projected_wall.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:45:13 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/19 18:11:42 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_p_line(int line_h, t_img txtr, t_img screen, int x_screen, int txtr_x)
{
	t_clr	*first_pxl;
	int		i_first_pxl;
	int 	pxl_pos;

	if (line_h > screen.height)
		line_h = screen.height;
	pxl_pos = 0;
	i_first_pxl = (screen.height - line_h) / 2;
	first_pxl = screen.p_data + x_screen + i_first_pxl * screen.width;
	i_first_pxl = 0;
	while (pxl_pos < line_h)
	{
		first_pxl[i_first_pxl] = txtr.p_data[txtr_x + txtr.height * (int)(txtr.width * pxl_pos / (float)line_h)];
		i_first_pxl += screen.width;
		++pxl_pos;
	}
}


void	draw_p_wall(t_img txtr, t_render *render, int x_start, int x_end, int y_start, int y_end, float p_start, float p_end)
{
	const float	step_p_x = txtr.width * (p_end - p_start) / (x_end - x_start);
	const float step_i_y = (y_end - y_start) / (float)(x_end - x_start);
	float	i_p_x;
	int	i;
	float i_y;

	i_y = y_start;
	i = 0;
	i_p_x = txtr.width * p_start;
	while (i < x_end - x_start)
	{
		draw_p_line((int)i_y, txtr, render->img, x_start + i, (int)i_p_x);
		i_y += step_i_y;
		i_p_x += step_p_x;
		++i;
	}
}
