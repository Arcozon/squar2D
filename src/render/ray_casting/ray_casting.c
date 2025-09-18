/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 13:56:33 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/18 11:24:18 by gaeudes          ###   ########.fr       */
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

__attribute__((flatten))
void	ray_casting(t_game *game)
{
	t_ray	ray;
	int		i;

	ft_memcpy(&ray.doors, game->doors, sizeof(game->doors));
	ray.any_doors = game->any_doors;
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
