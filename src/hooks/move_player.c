/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 16:06:20 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/28 18:30:00 by gaeudes          ###   ########.fr       */
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


static inline void	handle_2_dir(float p_delta[2], const float p_speed)
{
	float	norm_factor = (fabs(p_delta[X]) + fabs(p_delta[Y])) / p_speed;

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

static inline void	calc_colision(char *map[], const float p_coo[2], float p_delta[2])
{
	const float	next_pcoo[2] = {p_coo[X] + p_delta[X], p_coo[Y] + p_delta[Y]};

	if (map[(int)p_coo[Y]][(int)(next_pcoo[X] + HALF_P_SIZE)] == WALL_CHAR)
	{
		DEBUG("COL right")
		DEBUG("WALL: %d", (int)(next_pcoo[X] + HALF_P_SIZE))
		DEBUG("Pl: %f", p_coo[X])
		DEBUG("Pre: %f", p_delta[X])
		p_delta[X] = (int)(next_pcoo[X] + HALF_P_SIZE) - HALF_P_SIZE - p_coo[X];
		DEBUG("Post: %f", p_delta[X])
	}
	else if (map[(int)p_coo[Y]][(int)(next_pcoo[X] - HALF_P_SIZE)] == WALL_CHAR)
	{
		DEBUG("COL left")
		DEBUG("WALL: %d", (int)(next_pcoo[X] - HALF_P_SIZE))
		DEBUG("Pl: %f", p_coo[X])
		DEBUG("Pre: %f", p_delta[X])
		p_delta[X] = (int)(next_pcoo[X] + 1 - HALF_P_SIZE) + HALF_P_SIZE - p_coo[X];
		DEBUG("Post: %f", p_delta[X])
	}
	if (map[(int)(next_pcoo[Y] + HALF_P_SIZE)][(int)(p_coo[X])] == WALL_CHAR)
	{
		DEBUG("COL bot")
		DEBUG("WALL: %d", (int)(next_pcoo[Y] + HALF_P_SIZE))
		DEBUG("Pl: %f", p_coo[Y])
		DEBUG("Pre: %f", p_delta[Y])
		p_delta[Y] = (int)(next_pcoo[Y] + HALF_P_SIZE) - HALF_P_SIZE - p_coo[Y];
		DEBUG("Post: %f", p_delta[Y])
	}
	else if (map[(int)(next_pcoo[Y] - HALF_P_SIZE)][(int)(p_coo[X])] == WALL_CHAR)
	{
		DEBUG("COL top")
		DEBUG("WALL: %d", (int)(next_pcoo[Y] - HALF_P_SIZE))
		DEBUG("Pl: %f", p_coo[Y])
		DEBUG("Pre: %f", p_delta[Y])
		p_delta[Y] = (int)(next_pcoo[Y] + 1 - HALF_P_SIZE) + HALF_P_SIZE - p_coo[Y];
		DEBUG("Post: %f", p_delta[Y])
	}
}

__attribute__((flatten))
void	move_player(t_game *game)
{
	handle_view_angle(game);
	get_new_delta(game, game->p_delta);
	calc_colision(game->map, game->p_coo, game->p_delta);
	game->p_coo[X] += game->p_delta[X];
	game->p_coo[Y] += game->p_delta[Y];
	ft_bzero(game->p_delta, sizeof(game->p_delta));
}
