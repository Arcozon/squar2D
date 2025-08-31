/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colision.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 13:56:33 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/31 18:55:29 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct	s_col
{
	float	distance[2];
	float	coo[2];

	float	teta_step;
	float	teta;
	float	sin_t;
	float	cos_t;
}	t_col;


void	check_colisions(t_game *game)
{
	t_col	col;
	int		i;

	col.teta_step = game->fov / W_WIDTH;
	col.teta = game->p_angle + col.teta_step * W_WIDTH / 2;
	i = 0;
	while (i < W_WIDTH)
	{
		// DEBUG("%d: %f", i, col.teta)
		col.teta += col.teta_step;
		++i;
	}
	// DEBUG("player %f", game->p_angle)
	// DEBUG("fov: %f| start: %f, end: %f", game->fov, game->p_angle + col.teta_step * W_WIDTH / 2, game->p_angle - col.teta_step * W_WIDTH / 2)
	// WAITd
}
