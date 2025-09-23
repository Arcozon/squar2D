/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 16:06:20 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/23 17:30:17 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
# define VANGLE_DELTA 0.05f
__attribute__((always_inline))
static inline void	handle_view_angle(t_game *game)
{
	if (game->f_keys & HOOK_M_LARR && !(game->f_keys & HOOK_M_RARR))
		game->p_angle += game->angle_speed;
	else if (game->f_keys & HOOK_M_RARR && !(game->f_keys & HOOK_M_LARR))
		game->p_angle -= game->angle_speed;
}

__attribute__((always_inline))
static inline void	handle_2_dir(float p_delta[2], const float p_speed)
{
	const float	dist2 = p_delta[X] * p_delta[X] + p_delta[Y] * p_delta[Y];
	const float	norm_factor = sqrtf(dist2) / p_speed;

	p_delta[X] /= norm_factor;
	p_delta[Y] /= norm_factor;
}

__attribute__((always_inline, flatten))
static inline void	get_new_delta(const t_game *game, float p_delta[2])
{
	if (game->f_keys & HOOK_M_W && !(game->f_keys & HOOK_M_S))
	{
		p_delta[X] += cos(game->p_angle) * game->p_speed;
		p_delta[Y] -= sin(game->p_angle) * game->p_speed;
	}
	else if (game->f_keys & HOOK_M_S && !(game->f_keys & HOOK_M_W))
	{
		p_delta[X] -= cos(game->p_angle) * game->p_speed;
		p_delta[Y] += sin(game->p_angle) * game->p_speed;
	}
	if (game->f_keys & HOOK_M_A && !(game->f_keys & HOOK_M_D))
	{
		p_delta[X] += cos(game->p_angle + M_PI_2) * game->p_speed;
		p_delta[Y] -= sin(game->p_angle + M_PI_2) * game->p_speed;
	}
	else if (game->f_keys & HOOK_M_D && !(game->f_keys & HOOK_M_A))
	{
		p_delta[X] -= cos(game->p_angle + M_PI_2) * game->p_speed;
		p_delta[Y] += sin(game->p_angle + M_PI_2) * game->p_speed;
	}
	if (((game->f_keys & HOOK_M_W) != 0) ^ ((game->f_keys & HOOK_M_S) != 0)
		&& ((game->f_keys & HOOK_M_A) != 0) ^ ((game->f_keys & HOOK_M_D) != 0))
		handle_2_dir(p_delta, game->p_speed);
}

__attribute__((flatten))
void	move_player(t_game *game)
{
	if (game->f_keys & HOOK_M_UARR && !(game->f_keys & HOOK_M_DARR))
		game->fov += VANGLE_DELTA;
	else if (game->f_keys & HOOK_M_DARR && !(game->f_keys & HOOK_M_UARR))
		game->fov -= VANGLE_DELTA;
	handle_view_angle(game);
	get_new_delta(game, game->p_delta);
	check_colisions(game->p_coo, game->p_delta, game->map, game);
	game->p_coo[X] += game->p_delta[X];
	game->p_coo[Y] += game->p_delta[Y];
	ft_bzero(game->p_delta, sizeof(game->p_delta));
}
