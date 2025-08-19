/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:34:08 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/19 17:29:45 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_frame(t_game *game)
{
	set_floor_ceiling(&game->render);
	draw_p_wall(game->render.n_txtr, &game->render, 100, 200, 500, 200);
	draw_p_wall(game->render.s_txtr, &game->render, 900, 1200, 200, 600);
	draw_p_wall(game->render.w_txtr, &game->render, 250, 400, 200, 140);
	draw_p_wall(game->render.w_txtr, &game->render, 400, 550, 140, 80);
	draw_p_wall(game->render.w_txtr, &game->render, 550, 700, 80, 20);
	draw_p_wall(game->render.e_txtr, &game->render, 700, 850, 20, 80);
	mlx_put_image_to_window(game->render.pmlx, game->render.pwin,
		game->render.img.p_img, 0, 0);
}
