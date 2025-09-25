/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colision.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:50:55 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/25 13:25:36 by gaeudes          ###   ########.fr       */
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
			if (door->e_or == D_OR_HOR && (coo_x>= (float)door->x)
				&& (coo_x <= door->x + door->closed_percent)
				&& (coo_y >= (float)door->y)
				&& (coo_y <= (float)door->y + 1.f))
				return (door);
			else if (door->e_or == D_OR_VER && (coo_x >= (float)door->x)
					&& (coo_x <= (float)door->x + 1.f)
					&& (coo_y >= (float)door->y)
					&& (coo_y <= door->y + door->closed_percent))
				return (door);
			door = door->next;
		}
		++i;
	}
	return (NULL);
}

void __new_delta_door()
{
	fabsf(dist_door[X]) > fabsf(coo[X] - door->x - d_size[X]))
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

__attribute__((always_inline))
static inline void	__col_doors(const t_doors doors, const float coo[2],
	float p_delta[2], const float n_coo[2])
{
	const t_one_door	door_diag = __is_in_door(doors, n_coo[X], n_coo[Y]);
	const t_one_door	door_nx = __is_in_door(doors, n_coo[X], coo[Y]);
	const t_one_door	door_ny = __is_in_door(doors, coo[X], n_coo[Y]);

	if (door_diag && !door_nx && !door_ny)
	{

	}
	(void)p_delta;
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

	if (crossed[X] && crossed[Y] && map[(int)n_coo[Y]][(int)n_coo[X]]
		== WALL_CHAR && !is_in_wall[Y] && !is_in_wall[X])
	{
		if (p_delta[X] > p_delta[Y])
			p_delta[X] = __get_new_delta(coo[X], n_coo[X], p_delta[X] < 0);
		else
			p_delta[Y] = __get_new_delta(coo[Y], n_coo[Y], p_delta[Y] < 0);
	}
	else
	{
		if (crossed[X] && is_in_wall[X])
			p_delta[X] = __get_new_delta(coo[X], n_coo[X], p_delta[X] < 0);
		if (crossed[Y] && is_in_wall[Y])
			p_delta[Y] = __get_new_delta(coo[Y], n_coo[Y], p_delta[Y] < 0);
	}
	if (game->any_doors)
		__col_doors(game->doors, coo, p_delta, n_coo);
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
