/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colision.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 13:56:33 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/05 15:03:21 by gaeudes          ###   ########.fr       */
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
	float		percent;
	float		distance;
}	t_col;

void	init_one_colision(t_col *col, t_game *game)
{
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

__attribute__((always_inline))
static inline void	get_next_step(t_col *col)
{
	col->i_coo[X] = (int)col->f_coo[X];
	col->i_coo[Y] = (int)col->f_coo[Y];
	col->next_step[X] = (col->i_coo[X] + col->add_thing[X]) - col->f_coo[X];
	col->next_step[Y] = (col->i_coo[Y] + col->add_thing[Y]) - col->f_coo[Y];
	if (col->next_step[Y] == 0.f)
		col->next_step[Y] = -1;
	if (col->next_step[X] == 0.f)
		col->next_step[X] = 1;
	if (!col->is_cos_null)
		col->distance_next_step[X] = col->next_step[X] / col->cos_t;
	else
		col->distance_next_step[X] = INFINITY;
	if (!col->is_sin_null)
		col->distance_next_step[Y] = col->next_step[Y] / - col->sin_t;
	else
		col->distance_next_step[Y] = INFINITY;
}

void	check_one_colision(t_col *col, char **map)
{
	while (col->hit == no_hit)
	{
		get_next_step(col);
		if (fabsf(col->distance_next_step[X]) <= fabsf(col->distance_next_step[Y]))
		{
			col->f_coo[X] = col->i_coo[X] + col->add_thing[X];
			col->f_coo[Y] -= col->distance_next_step[X] * col->sin_t;
		}
		else
		{
			col->f_coo[X] += col->distance_next_step[Y] * col->cos_t;
			col->f_coo[Y] = col->i_coo[Y] + col->add_thing[Y];
		}
		col->hit = __check_col(col, map);
	}
	DEBUG("finalHit: [%f|%f]", col->f_coo[X], col->f_coo[Y])
	if (col->hit == hor_hit)
	{
		col->percent = col->f_coo[X] - (int)col->f_coo[X];
		if (col->dir[X] < 0)
			col->percent = 1 - col->percent;
		DEBUG("HOR HIT %.1f%%", col->percent * 100)
	}
	else if (col->hit == ver_hit)
	{
		col->percent = col->f_coo[Y] - (int)col->f_coo[Y];
		if (col->dir[Y] > 0)
			col->percent = 1 - col->percent;
		DEBUG("VER HIT %.1f%%", col->percent * 100)
	}
	else
	{
		DEBUG("CORNER HIT")
	}
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
	DEBUG("DISTANCE: %f", fabs((col.f_coo[X] - game->p_coo[X]) / col.sin_t))
	write(2, "\n", 1);

	col.teta =  M_PI / 4;
	init_one_colision(&col, game);
	check_one_colision(&col, game->map);
	DEBUG("DISTANCE: %f", fabs((col.f_coo[X] - game->p_coo[X]) / col.sin_t))
	write(2, "\n", 1);

	col.teta =  - M_PI / 4;
	init_one_colision(&col, game);
	check_one_colision(&col, game->map);
	DEBUG("DISTANCE: %f", fabs((col.f_coo[X] - game->p_coo[X]) / col.sin_t))
	write(2, "\n", 1);

	col.teta =  - 3 * M_PI / 4;
	init_one_colision(&col, game);
	check_one_colision(&col, game->map);
	DEBUG("DISTANCE: %f", fabs((col.f_coo[X] - game->p_coo[X]) / col.sin_t))
	
	// exit(0);
	// i = 0;
	// while (i < W_WIDTH)
	// {
	// 	init_one_colision(&col, game);
	// 	check_one_colision(&col);
	// 	col.teta += col.teta_step;
	// 	++i;
	// }
}
