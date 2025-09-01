/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colision.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 13:56:33 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/01 17:00:58 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct	s_col
{
	float	distance[2];
	float	f_coo[2];

	float	teta_step;
	float	teta;
	float	sin_t;
	float	cos_t;
	
	float	step[2];
	int		i_coo[2];
}	t_col;

void	init_one_colision(t_col *col, t_game *game)
{
	col->distance[X] = 0.f;
	col->distance[Y] = 0.f;
	col->f_coo[X] = game->p_coo[X];
	col->f_coo[Y] = game->p_coo[Y];
	col->sin_t = sin(col->teta);
	col->cos_t = cos(col->teta);
	col->step[X] = 0;

}

void	check_one_colision(t_col *colt_game)
{
	
}

void	check_colisions(t_game *game)
{
	t_col	col;
	int		i;

	col.teta_step = game->fov / W_WIDTH;
	col.teta = game->p_angle + col.teta_step * W_WIDTH / 2;
	i = 0;
	while (i < W_WIDTH)
	{
		col.teta += col.teta_step;
		init_one_colision(&col, game);
		check_one_colision(&col);
		++i;
	}
}
