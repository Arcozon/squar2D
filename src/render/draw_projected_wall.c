/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_projected_wall.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:45:13 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/19 16:35:39 by gaeudes          ###   ########.fr       */
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
	// DEBUG("LINE_HEIGHT: %d", line_h)
	// DEBUG("sdfgsdfg: %d", x_screen + i_first_pxl * screen.width)
	// DEBUG("FIRST_PXL: %d | P_DATA: %p | P_FPXL: %p", i_first_pxl, screen.p_data, first_pxl)
	// WAIT
	i_first_pxl = 0;
	DEBUG("line_w = %d", txtr_x)
	while (pxl_pos < line_h)
	{
		// DEBUG("TXTR_P: %d", (int)(x_txtr + txtr.width * pxl_pos / (float)line_h))
		// DEBUG("%d: %x", (int)(txtr_x + txtr.width * pxl_pos / (float)line_h), txtr.p_data[(int)(txtr_x + txtr.width * pxl_pos / (float)line_h)]);
		DEBUG("%f: %d", pxl_pos / (float)line_h, txtr.height * (int)(txtr.width * pxl_pos / (float)line_h));
		first_pxl[i_first_pxl] = txtr.p_data[txtr_x + txtr.height * (int)(txtr.width * pxl_pos / (float)line_h)];
		i_first_pxl += screen.width;
		++pxl_pos;
	}
	// WAIT
}

void	draw_p_wall(t_img txtr, t_render *render)
{
	const int	x_start = 100;
	const int	x_end = 300;
	const int	y_start = 300;
	const int	y_end = 200;
	
	int	i_x = 0;

	DEBUG("%d:%d", txtr.height, txtr.width)
	DEBUG("%d:%d", render->img.height, render->img.width)
	// WAIT
	while (i_x < x_end - x_start)
	{
		// DEBUG("X: %d",x_start + i_x)
		// DEBUG("Y: %d - %d [%d]", y_start, y_end, (int)(y_start + i_x * (y_end - y_start) / (float)(x_end - x_start + 1)))
		// WAIT
		draw_p_line(y_start + i_x * (y_end - y_start) / (float)(x_end - x_start + 1), txtr, render->img, x_start + i_x, i_x * txtr.width / (float)( x_end - x_start));
		++i_x;
	}
	// WAIT
	// exit(1);

}
