/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:34:08 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/23 11:30:14 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_frame(t_game *game, t_render *render)
{
	set_floor_ceiling(render);
	render_minimap(game, render);
	antialiasing(render);
	cub_putimgtoimg(render->img_mmap, render->img_paa,
		(int []){MMAP_XSTART, MMAP_YSTART});
	mlx_put_image_to_window(render->pmlx, render->pwin,
		render->img_paa.p_img, 0, 0);
}
