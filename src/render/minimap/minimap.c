/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 11:33:17 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/23 11:23:06 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	mmap_player(t_img img_map, const uint32_t clr)
{
	static const int	center[] = {MMAP_WIDHT / 2, MMAP_HEIGHT / 2};
	int					ix;
	int					iy;

	iy = -MMAP_P_RADIUS;
	while (iy <= MMAP_P_RADIUS)
	{
		ix = -MMAP_P_RADIUS;
		while (ix <= MMAP_P_RADIUS)
		{
			if (ix * ix + iy * iy <= MMAP_P_RADIUS * MMAP_P_RADIUS)
			{
				img_map.p_data[center[X] + ix
					+ (center[Y] + iy) * img_map.width].rgb = clr;
			}
			++ix;
		}	
		++iy;
	}
}

void	render_minimap(t_game *game, t_render *render)
{
	render_mmap_environement(game->map, game->dim,
		game->p_coo, render);
	ray_casting(game);
	if (game->any_doors)
		mmap_doors(game->doors, render->img_mmap, game->p_coo, render->mmap_d_open); 
	mmap_player(render->img_mmap, render->mmap_player.rgb);
}
