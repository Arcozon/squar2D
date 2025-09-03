/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colision.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 13:56:33 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/03 12:59:06 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct	s_col
{
	float	distance[2];
	float	f_coo[2];
	int		i_coo[2];

	float	teta_step;
	float	teta;
	float	sin_t;
	float	cos_t;
	
	int		dir[2];
	int		add_thing[2];
}	t_col;

void	init_one_colision(t_col *col, t_game *game)
{
	col->distance[X] = 0.f;
	col->distance[Y] = 0.f;
	col->f_coo[X] = game->p_coo[X];
	col->f_coo[Y] = game->p_coo[Y];
	col->sin_t = sin(col->teta);
	col->cos_t = cos(col->teta);

	col->dir[X] = -1;
	col->add_thing[X] = 0;
	if (col->cos_t >= 0)
	{
		col->add_thing[X] = 1;
		col->dir[X] = 1;	
	}
	col->dir[Y] = 1;
	col->add_thing[Y] = 1; 
	if (col->sin_t >= 0)
	{
		col->add_thing[Y] = 0;
		col->dir[Y] = -1;
	}
}

void	check_one_colision(t_col *col)
{
	float	next_x;

	col->i_coo[X] = (int)col->f_coo[X];
	col->i_coo[Y] = (int)col->f_coo[Y];
	DEBUG("teta: %f", col->teta)

	// DEBUG("cX: %f", col->f_coo[X])
	// DEBUG("dirX: %d", col->dir[X])
	// DEBUG("tocheckX: %d", col->i_coo[X] + col->dir[X])
	// DEBUG("goalX: %d", col->i_coo[X] + col->add_thing[X])
	// DEBUG("dX :%f", (col->add_thing[X] - (col->f_coo[X] - col->i_coo[X])) * col->dir[X])
	// write(2, "\n", 1);

	DEBUG("cY: %f", col->f_coo[Y])
	DEBUG("dirY: %d", col->dir[Y])
	DEBUG("tocheckY: %d", col->i_coo[Y] + col->dir[Y])
	DEBUG("goalY: %d", col->i_coo[Y] + col->add_thing[Y])
	DEBUG("dY :%f", (col->add_thing[Y] - (col->f_coo[Y] - col->i_coo[Y])) * col->dir[Y])

	(void)next_x;
	(void)col;
}

void	check_colisions(t_game *game)
{
	t_col	col;
	// int		i;
	col.teta_step = game->fov / W_WIDTH;

	game->p_coo[X] = 1.4f;
	game->p_coo[Y] = 1.6f;

	col.teta = game->p_angle + game->fov / 2;
	init_one_colision(&col, game);
	check_one_colision(&col);
	
	write(2, "\n\n", 2);


	col.teta = game->p_angle - game->fov / 2 - 1;
	init_one_colision(&col, game);
	check_one_colision(&col);

	exit(0);
	// i = 0;
	// while (i < W_WIDTH)
	// {
	// 	init_one_colision(&col, game);
	// 	check_one_colision(&col);
	// 	col.teta += col.teta_step;
	// 	++i;
	// }
}
