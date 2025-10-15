/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 11:10:21 by gaeudes           #+#    #+#             */
/*   Updated: 2025/10/14 17:52:20 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

__attribute__((always_inline))
static inline enum e_hit	__chech_door_edge(t_ray *ray, t_c_door door)
{
	const float	s_c = ray->sin_t / ray->cos_t;
	const float	c_s = ray->cos_t / ray->sin_t;

	if (door->e_or == D_OR_VER)
	{
		if (ray->f_coo[Y] - ray->dir[X] * s_c < door->closed_percent + door->y)
		{
			ray->f_coo[X] += (ray->f_coo[Y] - (int)(ray->f_coo[Y])
					- door->closed_percent) * c_s;
			ray->f_coo[Y] = (int)ray->f_coo[Y] + door->closed_percent;
			ray->percent = ray->f_coo[X] - (int)ray->f_coo[X];
			return (ray->hit = door_hor_hit);
		}
	}
	else if (ray->f_coo[X] - ray->dir[Y] * c_s < door->closed_percent + door->x)
	{
		ray->f_coo[Y] += (ray->f_coo[X] - (int)(ray->f_coo[X])
				- door->closed_percent) * s_c;
		ray->f_coo[X] = (int)ray->f_coo[X] + door->closed_percent;
		ray->percent = 1 - (ray->f_coo[Y] - (int)ray->f_coo[Y]);
		return (ray->hit = door_hor_hit);
	}
	return (no_hit);
}

__attribute__((always_inline))
static inline enum e_hit	__check_one_coo(t_ray *ray, const int to_check[2],
	char **map, const enum e_hit orientation)
{
	t_one_door	the_one;

	if (map[to_check[Y]][to_check[X]] == WALL_CHAR)
		return (ray->hit = orientation);
	else if (!ray->any_doors)
		return (no_hit);
	the_one = find_door(ray->doors, to_check[X], to_check[Y]);
	if (!the_one)
		return (no_hit);
	ray->percent = ray->f_coo[X] - (int)ray->f_coo[X];
	if (orientation == hor_hit)
		if (ray->dir[Y] > 0)
			ray->percent = ray->percent;
	if (orientation == ver_hit)
	{
		ray->percent = ray->f_coo[Y] - (int)ray->f_coo[Y];
		if (ray->dir[X] < 0)
			ray->percent = ray->percent;
	}
	if (the_one->closed_percent > ray->percent)
	{
		ray->percent = 1 - the_one->closed_percent + ray->percent;
		return (ray->hit = orientation + (door_hor_hit - hor_hit));
	}
	return (__chech_door_edge(ray, the_one));
}

__attribute__((always_inline))
static inline enum e_hit	__check_ray(t_ray *ray, char **map)
{
	if (fabsf(ray->dist_n_step[X]) < fabsf(ray->dist_n_step[Y]))
	{
		return (__check_one_coo(ray,
				(int []){(int)ray->f_coo[X] + ray->for_check[X],
				(int)ray->f_coo[Y]}, map, ver_hit));
	}
	else if (fabsf(ray->dist_n_step[X]) > fabsf(ray->dist_n_step[Y]))
	{
		return (__check_one_coo(ray, (int []){(int)ray->f_coo[X],
				(int)ray->f_coo[Y] + ray->for_check[Y]}, map, hor_hit));
	}
	else
	{
		if (__check_one_coo(ray, (int []){(int)ray->f_coo[X] + ray->dir[X],
				(int)ray->f_coo[Y]}, map, hor_hit))
			return (ray->hit);
		if (__check_one_coo(ray, (int []){(int)ray->f_coo[X],
				(int)ray->f_coo[Y] + ray->dir[Y]}, map, ver_hit))
			return (ray->hit);
		if (__check_one_coo(ray, (int []){(int)ray->f_coo[X] + ray->dir[X],
				(int)ray->f_coo[Y] + ray->dir[Y]}, map, ver_hit))
			return (ray->hit);
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

__attribute__((flatten))
void	__check_one_ray(t_ray *ray, char **map)
{
	__get_n_step(ray);
	if (find_door(ray->doors, ray->i_coo[X], ray->i_coo[Y]))
		only_chech_door_edge(ray,
			find_door(ray->doors, ray->i_coo[X], ray->i_coo[Y]));
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
}
