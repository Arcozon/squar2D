/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colision.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:50:55 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/23 18:07:07 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

__attribute__((always_inline, const))
static inline t_c_door	__is_in_door(const t_doors doors, const float n_coo[2])
{
	t_c_door	door;
	uint32_t	i;

	i = 0;
	while (i < N_HASH_DOORS)
	{
		door = doors[i];
		while (door)
		{
			if (door->e_or == D_OR_HOR && (n_coo[X] >= (float)door->x)
				&& (n_coo[X] <= door->x + door->closed_percent)
				&& (n_coo[Y] >= (float)door->y)
				&& (n_coo[Y] <= (float)door->y + 1.f))
				return (door);
			else if (door->e_or == D_OR_VER && (n_coo[X] >= (float)door->x)
					&& (n_coo[X] <= (float)door->x + 1.f)
					&& (n_coo[Y] >= (float)door->y)
					&& (n_coo[Y] <= door->y + door->closed_percent))
				return (door);
			door = door->next;
		}
		++i;
	}
	return (0);
}

// __attribute__((always_inline))
// static inline void	__one_col_door(t_c_door door, const float coo[2],
// 	float p_delta[2])
// {
// 	float	d_size[2];
// 	float	dist_door[2];

// 	if (!door)
// 		return ;
// 	d_size[X] = 1.f;
// 	d_size[Y] = 1.f;
// 	if (door->e_or == D_OR_HOR)
// 		d_size[X] = door->closed_percent;
// 	else
// 		d_size[Y] = door->closed_percent;
// 	dist_door[X] = coo[X] - door->x;
// 	if (fabsf(dist_door[X]) > fabsf(coo[X] - door->x - d_size[X]))
// 		dist_door[X] = coo[X] - door->x - d_size[X];
// 	dist_door[Y] = coo[Y] - door->y;
// 	if (fabsf(dist_door[Y]) > fabsf(coo[Y] - door->y - d_size[Y]))
// 		dist_door[Y] = coo[Y] - door->y - d_size[Y];
// 	if (fabsf(p_delta[X]) > fabsf(dist_door[X]))
// 		p_delta[X] = -dist_door[X];
// 	if (fabsf(p_delta[Y]) > fabsf(dist_door[Y]))
// 		p_delta[Y] = -dist_door[Y];
// }

__attribute__((always_inline))
static inline void	__one_col_door(t_c_door door, const float coo[2],
	float p_delta[2])
{
	float	d_size[2];
	float	dist_door[2];

	if (!door)
		return ;
	d_size[X] = 1.f;
	d_size[Y] = 1.f;
	if (door->e_or == D_OR_HOR)
		d_size[X] = door->closed_percent;
	else
		d_size[Y] = door->closed_percent;
	dist_door[X] = door->x - coo[X];
	if (fabsf(dist_door[X]) > fabsf(coo[X] - door->x - d_size[X]))
		dist_door[X] = (door->x + d_size[X]) - coo[X];
	dist_door[Y] = door->y - coo[Y];
	if (fabsf(dist_door[Y]) > fabsf(coo[Y] - door->y - d_size[Y]))
		dist_door[Y] = (door->y + d_size[Y]) - coo[Y];
	if (fabsf(dist_door[Y]) > fabsf(dist_door[X]))
	{
		if (p_delta[X] >= 0)
			dist_door[X] -= ZERO_RANGE;
		p_delta[X] = dist_door[X];
	}
	else
	{
		if (p_delta[Y] >= 0)
			dist_door[Y] -= ZERO_RANGE;
		p_delta[Y] = dist_door[Y];
	}
}

__attribute__((always_inline, const))
static inline float	__get_new_delta(const float old_coo,
	const float new_coo, const int to_add)
{
	if (to_add)
		return ((int)(new_coo + 1) - old_coo);
	else
		return ((int)(new_coo) - old_coo - ZERO_RANGE);
}

__attribute__((always_inline))
static inline void	__check_one_col(char *map[],
	const float coo[2], float p_delta[2], const t_game *game)
{
	const float	n_coo[2] = {coo[X] + p_delta[X], coo[Y] + p_delta[Y]};
	const int	crossed[2] = {(int)coo[X] != (int)n_coo[X],
		(int)coo[Y] != (int)n_coo[Y]};
	const int	is_in_wall[2] = {
		map[(int)coo[Y]][(int)n_coo[X]] == WALL_CHAR,
		map[(int)n_coo[Y]][(int)coo[X]] == WALL_CHAR
	};
	const t_c_door	hit_door[2] = {__is_in_door(game->doors, (float []){n_coo[X], coo[Y]}),
			__is_in_door(game->doors, (float []){coo[X], n_coo[Y]})};

	if (crossed[X] && crossed[Y]
		&& map[(int)n_coo[Y]][(int)n_coo[X]] == WALL_CHAR
		&& !(is_in_wall[Y] || hit_door[Y]) && !(is_in_wall[X] || hit_door[X]))
	{
		p_delta[X] = __get_new_delta(coo[X], n_coo[X], p_delta[X] < 0);
		p_delta[Y] = __get_new_delta(coo[Y], n_coo[Y], p_delta[Y] < 0);
	}
	else
	{
		if (crossed[X] && is_in_wall[X] && !hit_door[X])
			p_delta[X] = __get_new_delta(coo[X], n_coo[X], p_delta[X] < 0);
		if (crossed[Y] && is_in_wall[Y] && !hit_door[Y])
			p_delta[Y] = __get_new_delta(coo[Y], n_coo[Y], p_delta[Y] < 0);
	}
	if (game->any_doors)
		__one_col_door(__is_in_door(game->doors, n_coo), coo, p_delta);
}

__attribute__((flatten))
void	check_colisions(const float p_coo[2], float p_delta[2], char *map[], const t_game *game)
{
	const float	coo_nw[2] = {p_coo[X] - HALF_P_SIZE, p_coo[Y] - HALF_P_SIZE};
	const float	coo_ne[2] = {p_coo[X] + HALF_P_SIZE, p_coo[Y] - HALF_P_SIZE};
	const float	coo_se[2] = {p_coo[X] + HALF_P_SIZE, p_coo[Y] + HALF_P_SIZE};
	const float	coo_sw[2] = {p_coo[X] - HALF_P_SIZE, p_coo[Y] + HALF_P_SIZE};

	if (p_delta[X] < 0)
	{
		if (p_delta[Y] < 0)
			__check_one_col(map, coo_nw, p_delta, game);
		else
			__check_one_col(map, coo_sw, p_delta, game);
	}
	else
	{
		if (p_delta[Y] < 0)
			__check_one_col(map, coo_ne, p_delta, game);
		else
			__check_one_col(map, coo_se, p_delta, game);
	}
	__check_one_col(map, coo_ne, p_delta, game);
	__check_one_col(map, coo_nw, p_delta, game);
	__check_one_col(map, coo_sw, p_delta, game);
	__check_one_col(map, coo_se, p_delta, game);
}
