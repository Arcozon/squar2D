/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 13:56:33 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/12 13:13:16 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

__attribute__((always_inline))
static inline void	__init_one_raycast(t_ray *ray, t_game *game)
{
	ray->f_coo[X] = game->p_coo[X];
	ray->f_coo[Y] = game->p_coo[Y];
	ray->sin_t = sin(ray->teta);
	ray->is_sin_null = (ray->sin_t >= -ZERO_RANGE && ray->sin_t <= ZERO_RANGE);
	ray->cos_t = cos(ray->teta);
	ray->is_cos_null = (ray->cos_t >= -ZERO_RANGE && ray->cos_t <= ZERO_RANGE);
	ray->dir[X] = -1;
	ray->add_thing[X] = 0;
	ray->for_check[X] = -1;
	if (ray->cos_t >= 0)
	{
		ray->add_thing[X] = 1;
		ray->for_check[X] = 0;
		ray->dir[X] = 1;
	}
	ray->dir[Y] = 1;
	ray->add_thing[Y] = 1;
	ray->for_check[Y] = 0;
	if (ray->sin_t >= 0)
	{
		ray->add_thing[Y] = 0;
		ray->for_check[Y] = -1;
		ray->dir[Y] = -1;
	}
	ray->hit = no_hit;
}

enum e_hit	__check_ray(const t_ray *ray, char **map)
{
	if (fabsf(ray->dist_n_step[X]) < fabsf(ray->dist_n_step[Y]))
	{
		if (map[(int)ray->f_coo[Y]][(int)ray->f_coo[X] + ray->for_check[X]]
			== WALL_CHAR)
			return (ver_hit);
	}
	else if (fabsf(ray->dist_n_step[X]) > fabsf(ray->dist_n_step[Y]))
	{
		if (map[(int)ray->f_coo[Y] + ray->for_check[Y]][(int)ray->f_coo[X]]
			== WALL_CHAR)
			return (hor_hit);
	}
	else
	{
		if (map[ray->i_coo[Y]][ray->i_coo[X] + ray->dir[X]] == WALL_CHAR)
			return (hor_hit);
		else if (map[ray->i_coo[Y] + ray->dir[Y]][ray->i_coo[X]]
			== WALL_CHAR)
			return (ver_hit);
		else if (map[ray->i_coo[Y] + ray->dir[Y]][ray->i_coo[X] + ray->dir[X]]
			== WALL_CHAR)
			return (corner_hit);
	}
	return (no_hit);
}

__attribute__((always_inline))
static inline void	__get_n_step(t_ray *ray)
{
	ray->i_coo[X] = (int)ray->f_coo[X];
	ray->i_coo[Y] = (int)ray->f_coo[Y];
	ray->n_step[X] = (ray->i_coo[X] + ray->add_thing[X]) - ray->f_coo[X];
	ray->n_step[Y] = (ray->i_coo[Y] + ray->add_thing[Y]) - ray->f_coo[Y];
	if (ray->n_step[Y] == 0.f)
		ray->n_step[Y] = -1;
	if (ray->n_step[X] == 0.f)
		ray->n_step[X] = -1;
	if (!ray->is_cos_null)
		ray->dist_n_step[X] = ray->n_step[X] / ray->cos_t;
	else
		ray->dist_n_step[X] = INFINITY;
	if (!ray->is_sin_null)
		ray->dist_n_step[Y] = ray->n_step[Y] / -ray->sin_t;
	else
		ray->dist_n_step[Y] = INFINITY;
}

__attribute__((always_inline))
static inline void	__check_one_ray(t_ray *ray, char **map)
{
	while (ray->hit == no_hit)
	{
		__get_n_step(ray);
		if (fabsf(ray->dist_n_step[X]) <= fabsf(ray->dist_n_step[Y]))
		{
			ray->f_coo[X] += ray->n_step[X];
			ray->f_coo[Y] -= ray->dist_n_step[X] * ray->sin_t;
		}
		else
		{
			ray->f_coo[X] += ray->dist_n_step[Y] * ray->cos_t;
			ray->f_coo[Y] += ray->n_step[Y];
		}
		ray->hit = __check_ray(ray, map);
	}
	if (ray->hit == hor_hit)
	{
		ray->side = north_side;
		ray->percent = ray->f_coo[X] - (int)ray->f_coo[X];
		if (ray->dir[Y] > 0)
		{
			ray->side = south_side;
			ray->percent = 1 - ray->percent;
		}
	}
	else
	{
		ray->side = east_side;
		ray->percent = ray->f_coo[Y] - (int)ray->f_coo[Y];
		if (ray->dir[X] < 0)
		{
			ray->side = west_side;
			ray->percent = 1 - ray->percent;
		}
	}
}

__attribute__((always_inline))
static inline void	__call_draw_ray_wall(const t_ray ray,
	const int x, const t_game game, t_render render)
{
	const float	dx = (ray.f_coo[X] - game.p_coo[X]);
	const float	dy = (ray.f_coo[Y] - game.p_coo[Y]);
	t_dcwall	info;

	if (ray.side == north_side)
		info.wall_img = render.n_txtr;
	else if (ray.side == east_side)
		info.wall_img = render.e_txtr;
	else if (ray.side == south_side)
		info.wall_img = render.s_txtr;
	else if (ray.side == west_side)
		info.wall_img = render.w_txtr;
	info.img_percent = ray.percent;
	info.distance = sqrtf(dx * dx + dy * dy);
	draw_col_wall(info, render.img, x, info.wall_img);
}

void	ray_casting(t_game *game)
{
	t_ray	ray;
	int		i;

	ray.teta_step = game->fov / W_WIDTH;
	ray.teta = game->p_angle + game->fov / 2;
	i = 0;
	while (i < W_WIDTH)
	{
		__init_one_raycast(&ray, game);
		__check_one_ray(&ray, game->map);
		render_mmap_one_ray(game, ray);
		__call_draw_ray_wall(ray, i, *game, game->render);
		ray.teta -= ray.teta_step;
		++i;
	}
}
