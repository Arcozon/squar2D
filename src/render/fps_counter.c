/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_counter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:48:29 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/30 18:57:50 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define MICRO_S_PER_S		1000000LU
#define NANO_S_PER_MICRO_S	1000L

#define TIME_RANGE_FPS		100000LU

#define MIN_FPS				50
#define FPS_PRECISION		100

#define MLX_PXL_CHAR_WIDTH	6

#define MARGE_X				5
#define MARGE_Y				14

__attribute__((always_inline, flatten))
static inline void	__get_new_count(const t_microsec elasped_time, t_game *game)
{
	uint64_t	fps;
	uint64_t	fps_decimals;
	uint64_t	len_predecimal;

	game->buffer_fps[0] = '\0';
	fps = (game->frame_count * MICRO_S_PER_S) / elasped_time;
	ft_lutoacpy(game->buffer_fps, fps, sizeof(game->buffer_fps));
	if (fps < MIN_FPS)
	{
		fps_decimals = (game->frame_count * FPS_PRECISION
				* MICRO_S_PER_S) / elasped_time;
		fps_decimals %= FPS_PRECISION;
		if (fps_decimals)
		{
			ft_strlcat(game->buffer_fps, ".", sizeof(game->buffer_fps));
			len_predecimal = ft_strlen(game->buffer_fps);
			ft_lutoacpy(&game->buffer_fps[len_predecimal], fps_decimals,
				sizeof(game->buffer_fps) - len_predecimal);
		}
	}
	ft_strlcat(game->buffer_fps, " FPS", sizeof(game->buffer_fps));
	game->len_buffer_fps = ft_strlen(game->buffer_fps);
}

void	handle_fps(t_game *game)
{
	t_timespec	act_time;
	t_microsec	elapsed_time;

	++game->frame_count;
	if (clock_gettime(CLOCK_MONOTONIC, &act_time))
		return ;
	elapsed_time = (act_time.tv_sec - game->last_time.tv_sec) * MICRO_S_PER_S
		+ (act_time.tv_nsec - game->last_time.tv_nsec) / NANO_S_PER_MICRO_S;
	if (elapsed_time >= TIME_RANGE_FPS)
	{
		game->last_time = act_time;
		__get_new_count(elapsed_time, game);
		game->frame_count = 0;
	}
	mlx_string_put(game->render.pmlx, game->render.pwin,
		W_WIDTH - MLX_PXL_CHAR_WIDTH * game->len_buffer_fps - MARGE_X, MARGE_Y,
		game->render.fps_counter.rgb, game->buffer_fps);
}
