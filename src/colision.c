/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colision.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 13:56:33 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/05 14:38:57 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define ZERO_RANGE	0.000005f

enum	e_hit
{
	no_hit = 0,
	hor_hit,
	ver_hit,
	corner_hit
};

typedef struct	s_col
{
	float	distance[2];
	float	f_coo[2];
	int		i_coo[2];
	float	next_step[2];
	float	distance_next_step[2];

	float	teta_step;
	float	teta;
	float	slope;
	float	sin_t;
	int		is_sin_null;
	float	cos_t;
	int		is_cos_null;
	
	float	d_nextint[2];
	int		dir[2];
	int		add_thing[2];

	int		for_check[2];

	enum e_hit	hit;
}	t_col;

void	init_one_colision(t_col *col, t_game *game)
{
	col->distance[X] = 0.f;
	col->distance[Y] = 0.f;
	col->f_coo[X] = game->p_coo[X];
	col->f_coo[Y] = game->p_coo[Y];
	col->sin_t = sin(col->teta);
	col->is_sin_null = col->sin_t >= -ZERO_RANGE && col->sin_t <= ZERO_RANGE;
	col->slope = -col->sin_t;
	col->cos_t = cos(col->teta);
	col->is_cos_null = col->cos_t >= -ZERO_RANGE && col->cos_t <= ZERO_RANGE;

	col->dir[X] = -1;
	col->add_thing[X] = 0;
	col->for_check[X] = -1;
	if (col->cos_t >= 0)
	{
		col->add_thing[X] = 1;
		col->for_check[X] = 0;
		col->dir[X] = 1;	
	}
	col->dir[Y] = 1;
	col->add_thing[Y] = 1;
	col->for_check[Y] = 0;
	if (col->sin_t >= 0)
	{
		col->for_check[Y] = -1;
		col->add_thing[Y] = 0;
		col->dir[Y] = -1;
	}
	col->hit = no_hit;
}

// DEBUG("dirX: %d", col->dir[X])
// DEBUG("tocheckX: %d", col->i_coo[X] + col->dir[X])
// DEBUG("goalX: %d", col->i_coo[X] + col->add_thing[X])
// DEBUG("dirY: %d", col->dir[Y])
// DEBUG("tocheckY: %d", col->i_coo[Y] + col->dir[Y])
// DEBUG("goalY: %d", col->i_coo[Y] + col->add_thing[Y])

enum e_hit	__check_col(const t_col *col, char **map)
{
	if (fabsf(col->distance_next_step[X]) < fabsf(col->distance_next_step[Y]))
	{
		DEBUG("CHECK X [%d|%d]", (int)col->f_coo[X] + col->for_check[X], (int)col->f_coo[Y])
		if (map[(int)col->f_coo[Y]][(int)col->f_coo[X] + col->for_check[X]] == WALL_CHAR)
			return (ver_hit);
	}
	else if (fabsf(col->distance_next_step[X]) > fabsf(col->distance_next_step[Y]))
	{
		DEBUG("CHECK Y [%d|%d]", (int)col->f_coo[X], (int)col->f_coo[Y] + col->for_check[Y])
		if (map[(int)col->f_coo[Y] + col->for_check[Y]][(int)col->f_coo[X]] == WALL_CHAR)
			return (hor_hit);
	}
	else
	{
		DEBUG(" -- [%d|%d] [%d|%d] --",
			(int)col->f_coo[X] - col->for_check[X] - 1, col->i_coo[X],
			(int)col->f_coo[Y] - col->for_check[Y] - 1, col->i_coo[Y])
		DEBUG("CHECK OTHER[%d|%d] [%d|%d] [%d|%d]",
			col->dir[X],
			0,
			
			col->dir[X],
			col->dir[Y],
			
			0,
			col->dir[Y]
		)
		if (map[col->i_coo[Y]][col->i_coo[X] + col->dir[X]] == WALL_CHAR)
			return (hor_hit);
		else if (map[col->i_coo[Y] + col->dir[Y]][col->i_coo[X]] == WALL_CHAR)
			return (ver_hit);
		else if (map[col->i_coo[Y] + col->dir[Y]][col->i_coo[X] + col->dir[X]] == WALL_CHAR)
			return (corner_hit);
	}
	return (no_hit);
}

void	check_one_colision(t_col *col, char **map)
{
	DEBUG("c: [%f|%f] | teta: %f | s[%d]: %f | c[%d]: %f",  col->f_coo[X], col->f_coo[Y], col->teta, col->is_sin_null, col->sin_t, col->is_cos_null, col->cos_t)

	DEBUG("DIR : [%d|%d]", col->dir[X],col->dir[Y])
	// DEBUG("ADD : [%d|%d]", col->add_thing[X],col->add_thing[Y])
	DEBUG("CHECK : [%d|%d]", col->for_check[X],col->for_check[Y])
	while (col->hit == no_hit)
	{
		col->i_coo[X] = (int)col->f_coo[X];
		col->i_coo[Y] = (int)col->f_coo[Y];
		col->next_step[X] = (col->i_coo[X] + col->add_thing[X]) - col->f_coo[X];
		col->next_step[Y] = (col->i_coo[Y] + col->add_thing[Y]) - col->f_coo[Y];
		if (col->next_step[Y] == 0.f)
			col->next_step[Y] = -1;
		if (col->next_step[X] == 0.f)
			col->next_step[X] = 1;
		// DEBUG("-- X: %f %d %d  : %f", col->f_coo[X], col->i_coo[X], col->add_thing[X], col->next_step[X])
		// DEBUG("-- Y: %f %d %d  : %f", col->f_coo[Y], col->i_coo[Y], col->add_thing[Y], col->next_step[Y])
		if (!col->is_cos_null)
			col->distance_next_step[X] = col->next_step[X] / col->cos_t;
		else
			col->distance_next_step[X] = INFINITY;
		if (!col->is_sin_null)
			col->distance_next_step[Y] = col->next_step[Y] / - col->sin_t;
		else
			col->distance_next_step[Y] = INFINITY;
		// DEBUG("DistanceNext: [%f|%f]", col->distance_next_step[X], col->distance_next_step[Y])
		// DEBUG("StepNext: [%f|%f]", col->next_step[X], col->next_step[Y])
		if (fabsf(col->distance_next_step[X]) <= fabsf(col->distance_next_step[Y]))
		{
			col->f_coo[X] = col->i_coo[X] + col->add_thing[X];
			col->f_coo[Y] -= col->distance_next_step[X] * col->sin_t;
			// if (map[(int)col->f_coo[Y]][(int)col->f_coo[X] + col->for_check[X]] == WALL_CHAR)
			// 	col->hit = 1;
		}
		else //if (fabsf(col->distance_next_step[X]) > fabsf(col->distance_next_step[Y]))
		{
			col->f_coo[X] += col->distance_next_step[Y] * col->cos_t;
			col->f_coo[Y] = col->i_coo[Y] + col->add_thing[Y];
			// if (map[(int)col->f_coo[Y] + col->for_check[Y]][(int)col->f_coo[X]] == WALL_CHAR)
			// 	col->hit = 1;
		}
		col->hit = __check_col(col, map);
		DEBUG("NewC: [%f|%f]", col->f_coo[X], col->f_coo[Y])
	}
	DEBUG("finalHit: [%f|%f]", col->f_coo[X], col->f_coo[Y])
	if (col->hit == hor_hit)
	{
		DEBUG("HOR HIT")
	}
	else if (col->hit == ver_hit)
	{
		DEBUG("HOR HIT")
	}
	else
	{
		DEBUG("CORNER HIT")
	}
	(void) map;
}

void	check_colisions(t_game *game)
{
	t_col	col;
	// int		i;
	col.teta_step = game->fov / W_WIDTH;

	// game->p_coo[X] = 2.f;
	// game->p_coo[Y] = 2.f;
	col.teta = game->p_angle + game->fov / 2;

	col.teta =  3 * M_PI / 4;
	init_one_colision(&col, game);
	check_one_colision(&col, game->map);
	write(2, "\n", 1);

	col.teta =  M_PI / 4;
	init_one_colision(&col, game);
	check_one_colision(&col, game->map);
	write(2, "\n", 1);

	col.teta =  - M_PI / 4;
	init_one_colision(&col, game);
	check_one_colision(&col, game->map);
	write(2, "\n", 1);

	col.teta =  - 3 * M_PI / 4;
	init_one_colision(&col, game);
	check_one_colision(&col, game->map);
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
