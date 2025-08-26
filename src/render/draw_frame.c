/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:34:08 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/26 14:49:53 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	test_draw_shape(t_render *render)
{
	draw_p_wall(render->s_txtr, render, 0, 100, 120, 500, 0.f, 1.f);
	draw_p_wall(render->n_txtr, render, 100, 250, 500, 200, 0.5f, 1.f);
	draw_p_wall(render->s_txtr, render, 250, 400, 200, 340, 0.f, 0.5f);
	draw_p_wall(render->w_txtr, render, 400, 550, 140, 80, 0.f, 1.f);
	draw_p_wall(render->w_txtr, render, 550, 700, 80, 20, 0.f, 1.f);
	draw_p_wall(render->e_txtr, render, 700, 850, 20, 80, 0.f, 1.f);
	draw_p_wall(render->s_txtr, render, 850, 1200, 80, 600, 0.f, 1.f);
	draw_p_wall(render->n_txtr, render, 500, 700, 180, 200, 0.2f, 0.8f);
}

void	draw_frame(t_game *game, t_render *render)
{
	set_floor_ceiling(render);
	test_draw_shape(render);
	antialiasing(render);
	render_minimap(game, render);
	mlx_put_image_to_window(render->pmlx, render->pwin, render->img_paa.p_img, 0, 0);
	mlx_put_image_to_window(render->pmlx, render->pwin, render->img_mmap.p_img, MMAP_XSTART, MMAP_YSTART);
}
