/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colision_door.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:50:55 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/25 20:02:51 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void __new_delta_door()
// {
// 	fabsf(dist_door[X]) > fabsf(coo[X] - door->x - d_size[X]))
// 		dist_door[X] = (door->x + d_size[X]) - coo[X];
// 	dist_door[Y] = door->y - coo[Y];
// 	if (fabsf(dist_door[Y]) > fabsf(coo[Y] - door->y - d_size[Y]))
// 		dist_door[Y] = (door->y + d_size[Y]) - coo[Y];
// 	if (fabsf(dist_door[Y]) > fabsf(dist_door[X]))
// 	{
// 		if (p_delta[X] >= 0)
// 			dist_door[X] -= ZERO_RANGE;
// 		p_delta[X] = dist_door[X];
// 	}
// 	else
// 	{
// 		if (p_delta[Y] >= 0)
// 			dist_door[Y] -= ZERO_RANGE;
// 		p_delta[Y] = dist_door[Y];
// 	}
// }

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
			if (door->e_or == D_OR_HOR && (coo_x >= (float)door->x)
				&& (coo_x <= (float)door->x + door->closed_percent)
				&& (coo_y >= (float)door->y)
				&& (coo_y <= (float)door->y + VALUE_DOOR_CLOSED))
				return (door);
			else if (door->e_or == D_OR_VER && (coo_x >= (float)door->x)
					&& (coo_x <= (float)door->x + VALUE_DOOR_CLOSED)
					&& (coo_y >= (float)door->y)
					&& (coo_y <= (float)door->y + door->closed_percent))
				return (door);
			door = door->next;
		}
		++i;
	}
	return (NULL);
}

__attribute__((always_inline, flatten))
static inline void	__get_dist_door(t_c_door door, const float coo[2], float distance[2])
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
static inline void	__door_diag(t_c_door door, const float coo[2], float p_delta[2])
{
	float dist[2];

	DEBUG("here %f %f", p_delta[X], p_delta[Y]);
	DEBUG("here %f %f", coo[X], coo[Y]);
	__get_dist_door(door, coo, dist);
	DEBUG("dist %f %f", dist[X], dist[Y]);
	// if (dist[X] > p_delta[X])
	// 	dist[X] = p_delta[X];
	// if (dist[Y] > p_delta[Y])
	// 	dist[Y] = p_delta[Y];
	if (fabsf(dist[X] - p_delta[X]) < fabsf(dist[Y] - p_delta[Y]))
	{
		DEBUG("FIXED X")
		DEBUG("distX %f", dist[X]);
		if (p_delta[X] < 0.f)
			dist[X] += ZERO_RANGE;
		else
			dist[X] -= ZERO_RANGE;
		DEBUG("distX %f", dist[X]);
		p_delta[X] = dist[X];
	}
	else
	{
		DEBUG("FIXED Y")
		DEBUG("distY %f", dist[Y]);
		if (p_delta[Y] < 0.f)
			dist[Y] += ZERO_RANGE;
		else
			dist[Y] -= ZERO_RANGE;
		DEBUG("distY %f", dist[Y]);
		p_delta[Y] = dist[Y];
	}
	DEBUG(" NOW here %f %f", p_delta[X], p_delta[Y]);
	DEBUG(" NOW here %f %f", p_delta[X] + coo[X], coo[Y] + p_delta[Y]);
	WAIT;
}

__attribute__((always_inline, flatten))
static inline void	__door_side(t_c_door door, const float coo[2], float p_delta[2], int axis)
{
	float dist[2];

	__get_dist_door(door, coo, dist);
	if (axis == X)
	{
		if (p_delta[X] < 0.f)
			dist[X] += ZERO_RANGE;
		// else
		// 	dist[X] += ZERO_RANGE;
		p_delta[X] = dist[X];
	}
	else if (axis == Y)
	{
		if (p_delta[Y] < 0.f)
			dist[Y] += ZERO_RANGE;
		// else
		// 	dist[Y] -= ZERO_RANGE;
		p_delta[Y] = dist[Y];
	}
}

__attribute__((flatten))
void	colision_doors(const t_doors doors, const float coo[2],
	float p_delta[2], const int is_wall[2])
{
	const float	n_coo[2] = {coo[X] + p_delta[X], coo[Y] + p_delta[Y]};
	const t_c_door	door_diag = __is_in_door(doors, n_coo[X], n_coo[Y]);
	const t_c_door	door_nx = __is_in_door(doors, n_coo[X], coo[Y]);
	const t_c_door	door_ny = __is_in_door(doors, coo[X], n_coo[Y]);

	DEBUG("--- %d %d %d %d %d", door_diag > 0 , !door_nx , !door_ny , !is_wall[X] , !is_wall[Y])
	if (door_diag && !door_nx && !door_ny && !is_wall[X] && !is_wall[Y])
	{
		DEBUG("P_DELTA DIAG %f %f", p_delta[X], p_delta[Y]);
		__door_diag(door_diag, coo, p_delta);
		DEBUG("P_DELTA %f %f", p_delta[X], p_delta[Y]);// WAIT;
		if (__is_in_door(doors, coo[X] + p_delta[X], coo[Y] + p_delta[Y])
			|| __is_in_door(doors, coo[X], coo[Y] + p_delta[Y])
			|| __is_in_door(doors, coo[X] + p_delta[X], coo[Y]))
		{
			DEBUG("FCK")
			DEBUG("FCK %f %f", coo[X] + p_delta[X], coo[Y] + p_delta[Y])
			DEBUG("FCK %f %f", p_delta[X], p_delta[Y])
			WAIT;
		}
	}
	else
	{
		if (door_nx)
		{
			DEBUG("in X")
			DEBUG("%f | %f", coo[X], coo[Y])
			DEBUG("%f | %f", n_coo[X], coo[Y])
			DEBUG("P_DELTA %f %f", p_delta[X], p_delta[Y]);
			// __door_side(door_nx, (float []){coo[X], n_coo[Y]}, p_delta, X);
			__door_side(door_nx, (float []){n_coo[X], n_coo[Y]}, p_delta, X);
			DEBUG("P_DELTA %f %f", p_delta[X], p_delta[Y]);// WAIT;
		}
		else if (door_ny)
		{
			DEBUG("in y")
			DEBUG("%f | %f", coo[X], coo[Y])
			DEBUG("%f | %f", coo[X], n_coo[Y])
			DEBUG("P_DELTA %f %f", p_delta[X], p_delta[Y]);
			// __door_side(door_ny, (float []){n_coo[X], coo[Y]}, p_delta, Y);
			__door_side(door_ny, (float []){n_coo[X], n_coo[Y]}, p_delta, Y);
			// __door_side(door_ny, (float []){n_coo[X], coo[Y]}, p_delta, Y);
			DEBUG("P_DELTA %f %f", p_delta[X], p_delta[Y]); //WAIT;
		}
	}
	// if ((door_diag || door_nx || door_ny) && p_delta[Y] == 0.f)
		// WAIT
}

