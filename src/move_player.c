/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 16:06:20 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/25 16:42:11 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static inline void	handle_view_angle(t_game *game)
{
	if (game->f_keys & HOOK_M_LARR && !(game->f_keys & HOOK_M_RARR))
		game->p_angle += VANGLE_DELTA;
	else if (game->f_keys & HOOK_M_RARR)
		game->p_angle -= VANGLE_DELTA;
}

static inline void	get_new_coo(t_game *game, float new_coo[2])
{
	if (game->f_keys & HOOK_M_W && !(game->f_keys & HOOK_M_S))
	{
		new_coo[X] -= sin(game->p_angle) * game->p_speed;
		new_coo[Y] -= cos(game->p_angle) * game->p_speed;
	}
	else if (game->f_keys & HOOK_M_S)
	{
		new_coo[X] += sin(game->p_angle) * game->p_speed;
		new_coo[Y] += cos(game->p_angle) * game->p_speed;
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

static inline void	calc_colision(t_game *game, float new_coo[2])
{
	// Calc colision
	(void)game, (void)new_coo;
}

__attribute__((flatten))
void	move_player(t_game *game)
{
	float	new_coo[2];

	handle_view_angle(game);
	new_coo[X] = game->p_coo[X];
	new_coo[Y] = game->p_coo[Y];
	get_new_coo(game, new_coo);
	calc_colision(game, new_coo);
	game->p_coo[X] = new_coo[X];
	game->p_coo[Y] = new_coo[Y];
}
