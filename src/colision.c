/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colision.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 13:56:33 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/08 13:17:01 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

__attribute__((always_inline))
static inline void	init_one_colision(t_col *col, t_game *game)
{
	col->f_coo[X] = game->p_coo[X];
	col->f_coo[Y] = game->p_coo[Y];
	col->sin_t = sin(col->teta);
	col->is_sin_null = (col->sin_t >= -ZERO_RANGE && col->sin_t <= ZERO_RANGE);
	col->cos_t = cos(col->teta);
	col->is_cos_null = (col->cos_t >= -ZERO_RANGE && col->cos_t <= ZERO_RANGE);
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

enum e_hit	__check_col(const t_col *col, char **map)
{
	if (fabsf(col->dist_n_step[X]) < fabsf(col->dist_n_step[Y]))
	{
		if (map[(int)col->f_coo[Y]][(int)col->f_coo[X] + col->for_check[X]]
			== WALL_CHAR)
			return (ver_hit);
	}
	else if (fabsf(col->dist_n_step[X]) > fabsf(col->dist_n_step[Y]))
	{
		if (map[(int)col->f_coo[Y] + col->for_check[Y]][(int)col->f_coo[X]]
			== WALL_CHAR)
			return (hor_hit);
	}
	else
	{
		if (map[col->i_coo[Y]][col->i_coo[X] + col->dir[X]] == WALL_CHAR)
			return (hor_hit);
		else if (map[col->i_coo[Y] + col->dir[Y]][col->i_coo[X]]
			== WALL_CHAR)
			return (ver_hit);
		else if (map[col->i_coo[Y] + col->dir[Y]][col->i_coo[X] + col->dir[X]]
			== WALL_CHAR)
			return (corner_hit);
	}
	return (no_hit);
}

__attribute__((always_inline))
static inline void	get_n_step(t_col *col)
{
	col->i_coo[X] = (int)col->f_coo[X];
	col->i_coo[Y] = (int)col->f_coo[Y];
	col->n_step[X] = (col->i_coo[X] + col->add_thing[X]) - col->f_coo[X];
	col->n_step[Y] = (col->i_coo[Y] + col->add_thing[Y]) - col->f_coo[Y];
	if (col->n_step[Y] == 0.f)
		col->n_step[Y] = -1;
	if (col->n_step[X] == 0.f)
		col->n_step[X] = -1;
	if (!col->is_cos_null)
		col->dist_n_step[X] = col->n_step[X] / col->cos_t;
	else
		col->dist_n_step[X] = INFINITY;
	if (!col->is_sin_null)
		col->dist_n_step[Y] = col->n_step[Y] / -col->sin_t;
	else
		col->dist_n_step[Y] = INFINITY;
}

__attribute__((always_inline))
static inline void	check_one_colision(t_col *col, char **map)
{
	while (col->hit == no_hit)
	{
		get_n_step(col);
		if (fabsf(col->dist_n_step[X]) <= fabsf(col->dist_n_step[Y]))
		{
			col->f_coo[X] += col->n_step[X];
			col->f_coo[Y] -= col->dist_n_step[X] * col->sin_t;
		}
		else
		{
			col->f_coo[X] += col->dist_n_step[Y] * col->cos_t;
			col->f_coo[Y] += col->n_step[Y];
		}
		col->hit = __check_col(col, map);
	}
	if (col->hit == hor_hit)
	{
		col->side = north_side;
		col->percent = col->f_coo[X] - (int)col->f_coo[X];
		if (col->dir[Y] > 0)
		{
			col->side = south_side;
			col->percent = 1 - col->percent;
		}
	}
	else
	{
		col->side = east_side;
		col->percent = col->f_coo[Y] - (int)col->f_coo[Y];
		if (col->dir[X] < 0)
		{
			col->side = west_side;
			col->percent = 1 - col->percent;
		}
	}
}

__attribute__((always_inline))
static inline void	call_draw_col_wall(const t_col col,
	const int x, const t_game game, t_render render)
{
	const float	dx = (col.f_coo[X] - game.p_coo[X]);
	const float	dy = (col.f_coo[Y] - game.p_coo[Y]);
	t_dcwall	info;

	if (col.side == north_side)
		info.wall_img = render.n_txtr;
	else if (col.side == east_side)
		info.wall_img = render.e_txtr;
	else if (col.side == south_side)
		info.wall_img = render.s_txtr;
	else if (col.side == west_side)
		info.wall_img = render.w_txtr;
	info.img_percent = col.percent;
	info.distance = sqrtf(dx * dx + dy * dy);
	draw_col_wall(info, render.img, x, info.wall_img);
}

void	check_colisions(t_game *game)
{
	t_col	col;
	int		i;

	col.teta_step = game->fov / W_WIDTH;
	col.teta = game->p_angle + game->fov / 2;
	i = 0;
	while (i < W_WIDTH)
	{
		init_one_colision(&col, game);
		check_one_colision(&col, game->map);
		render_mmap_one_ray(game, col);
		call_draw_col_wall(col, i, *game, game->render);
		col.teta -= col.teta_step;
		++i;
	}
}
