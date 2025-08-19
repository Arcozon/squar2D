/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:34:08 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/19 18:05:56 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_frame(t_game *game)
{
	set_floor_ceiling(&game->render);
	draw_p_wall(game->render.s_txtr, &game->render, 0, 100, 120, 500, 0.f, 1.f);
	draw_p_wall(game->render.n_txtr, &game->render, 100, 250, 500, 200, 0.5f, 1.f);
	draw_p_wall(game->render.s_txtr, &game->render, 250, 400, 200, 340, 0.f, 0.5f);
	draw_p_wall(game->render.w_txtr, &game->render, 400, 550, 140, 80, 0.f, 1.f);
	draw_p_wall(game->render.w_txtr, &game->render, 550, 700, 80, 20, 0.f, 1.f);
	draw_p_wall(game->render.e_txtr, &game->render, 700, 850, 20, 80, 0.f, 1.f);
	draw_p_wall(game->render.s_txtr, &game->render, 850, 1200, 80, 600, 0.f, 1.f);
	draw_p_wall(game->render.n_txtr, &game->render, 500, 700, 180, 200, 0.2f, 0.8f);
	mlx_put_image_to_window(game->render.pmlx, game->render.pwin, game->render.img.p_img, 0, 0);
}
