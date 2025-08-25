/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 16:06:20 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/25 16:24:49 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

__attribute__((restrict))
static inline void	move_alldir(t_game *game, float new_coo[2])
{
	if (game->f_keys & HOOK_M_W && !(game->f_keys & HOOK_M_S))
	{
		new_coo[X] += sin(game->p_angle) * game->p_speed;
		new_coo[Y] += cos(game->p_angle) * game->p_speed;
	}
	else if (game->f_keys & HOOK_M_S)
	{
		new_coo[X] -= sin(game->p_angle) * game->p_speed;
		new_coo[Y] -= cos(game->p_angle) * game->p_speed;
	}
	if (game->f_keys & HOOK_M_A && !(game->f_keys & HOOK_M_D))
	{
		new_coo[X] += sin(game->p_angle + M_PI_2) * game->p_speed;
		new_coo[Y] += cos(game->p_angle + M_PI_2) * game->p_speed;
	}
	else if (game->f_keys & HOOK_M_D)
	{
		new_coo[X] -= sin(game->p_angle + M_PI_2) * game->p_speed;
		new_coo[Y] -= cos(game->p_angle + M_PI_2) * game->p_speed;
	}
}

void	move_player(t_game *game)
{
	float	new_coo[2];

	new_coo[X] = game->p_coo[X];
	new_coo[Y] = game->p_coo[Y];
	if (game->f_keys & HOOK_M_LARR && !(game->f_keys & HOOK_M_RARR))
		game->p_angle += VANGLE_DELTA;
	else if (game->f_keys & HOOK_M_RARR)
		game->p_angle -= VANGLE_DELTA;
	get_new_coo(game, new_coo);

}
