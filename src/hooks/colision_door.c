/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colision_door.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:50:55 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/27 13:51:40 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

__attribute__((always_inline, const))
static inline t_c_door	__is_in_door(const t_doors doors, const float coo_x,
	const float coo_y)
{
	t_c_door	door;
	uint32_t	i;

	i = 0;
	while (i < N_HASH_DOORS)
	{
		door = doors[i];
		while (door)
		{
			if (door->e_or == D_OR_HOR && (coo_x > (float)door->x)
				&& (coo_x < (float)door->x + door->closed_percent)
				&& (coo_y >= (float)door->y)
				&& (coo_y < (float)door->y + VALUE_DOOR_CLOSED))
				return (door);
			else if (door->e_or == D_OR_VER && (coo_x >= (float)door->x)
				&& (coo_x < (float)door->x + VALUE_DOOR_CLOSED)
				&& (coo_y >= (float)door->y)
				&& (coo_y < (float)door->y + door->closed_percent))
				return (door);
			door = door->next;
		}
		++i;
	}
	return (NULL);
}

__attribute__((always_inline, flatten))
static inline void	__get_dist_door(t_c_door door, const float coo[2],
	float distance[2])
{
	float	d_size[2];

	d_size[X] = VALUE_DOOR_CLOSED;
	d_size[Y] = VALUE_DOOR_CLOSED;
	if (door->e_or == D_OR_HOR)
		d_size[X] = door->closed_percent;
	else
		d_size[Y] = door->closed_percent;
	distance[X] = door->x - coo[X];
	if (fabsf(distance[X]) > fabsf(coo[X] - (door->x + d_size[X])))
		distance[X] = (door->x + d_size[X]) - coo[X];
	distance[Y] = door->y - coo[Y];
	if (fabsf(distance[Y]) > fabsf(coo[Y] - (door->y + d_size[Y])))
		distance[Y] = (door->y + d_size[Y]) - coo[Y];
}

__attribute__((always_inline, flatten))
static inline void	__door_diag(t_c_door door, const float coo[2],
	float p_delta[2])
{
	float	dist[2];

	__get_dist_door(door, coo, dist);
	if (fabsf(dist[X] - p_delta[X]) < fabsf(dist[Y] - p_delta[Y]))
	{
		if (p_delta[X] < 0.f)
			dist[X] += ZERO_RANGE;
		else
			dist[X] -= ZERO_RANGE;
		p_delta[X] = dist[X];
	}
	else
	{
		if (p_delta[Y] < 0.f)
			dist[Y] += ZERO_RANGE;
		else
			dist[Y] -= ZERO_RANGE;
		p_delta[Y] = dist[Y];
	}
}

__attribute__((always_inline, flatten))
static inline void	__door_side(t_c_door door, const float coo[2],
	float p_delta[2], const int axis)
{
	float	dist[2];

	__get_dist_door(door, coo, dist);
	if (axis == X)
	{
		p_delta[X] = dist[X];
		if (p_delta[X] > 0.f)
			p_delta[X] -= ZERO_RANGE;
		else
			p_delta[X] += ZERO_RANGE;
	}
	else
	{
		p_delta[Y] = dist[Y];
		if (p_delta[Y] > 0.f)
			p_delta[Y] -= ZERO_RANGE;
		else
			p_delta[Y] += ZERO_RANGE;
	}
}

__attribute__((flatten))
void	colision_doors(const t_doors doors, const float coo[2],
	float p_delta[2], const int is_wall[2])
{
	const float		n_coo[2] = {coo[X] + p_delta[X], coo[Y] + p_delta[Y]};
	const t_c_door	door_diag = __is_in_door(doors, n_coo[X], n_coo[Y]);
	const t_c_door	door_nx = __is_in_door(doors, n_coo[X], coo[Y]);
	const t_c_door	door_ny = __is_in_door(doors, coo[X], n_coo[Y]);

	if (door_diag && !door_nx && !door_ny && !is_wall[X] && !is_wall[Y])
		__door_diag(door_diag, coo, p_delta);
	else
	{
		if (door_nx && !is_wall[X])
			__door_side(door_nx, (float []){coo[X], coo[Y]}, p_delta, X);
		if (door_ny && !is_wall[Y])
			__door_side(door_ny, (float []){coo[X], coo[Y]}, p_delta, Y);
	}
}
