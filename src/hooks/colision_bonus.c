/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colision_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 18:18:16 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/27 13:49:42 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

__attribute__((always_inline, const))
static inline t_c_door	__is_in_door(const t_doors doors, const float coo_x,
	const float coo_y)
{
	const t_c_door	door = find_door(doors, (int)coo_x, (int)coo_y);

	if (!door)
		return (door);
	if (door->e_or == D_OR_HOR && (coo_x >= (float)door->x)
		&& (coo_x < door->x + door->closed_percent)
		&& (coo_y >= (float)door->y)
		&& (coo_y < (float)door->y + VALUE_DOOR_CLOSED))
		return (door);
	else if (door->e_or == D_OR_VER && (coo_x >= (float)door->x)
		&& (coo_x < (float)door->x + VALUE_DOOR_CLOSED)
		&& (coo_y >= (float)door->y)
		&& (coo_y < door->y + door->closed_percent))
		return (door);
	return (NULL);
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

__attribute__((always_inline, flatten))
static inline void	__check_one_col(char *map[],
	const float coo[2], float p_delta[2], const t_game *game)
{
	const float		n_coo[2] = {coo[X] + p_delta[X], coo[Y] + p_delta[Y]};
	const int		crossed[2] = {(int)coo[X] != (int)n_coo[X],
		(int)coo[Y] != (int)n_coo[Y]};
	const int		is_in_wall[2] = {map[(int)coo[Y]][(int)n_coo[X]]
		== WALL_CHAR, map[(int)n_coo[Y]][(int)coo[X]] == WALL_CHAR};

	if (crossed[X] && crossed[Y] && map[(int)n_coo[Y]][(int)n_coo[X]]
		== WALL_CHAR && !is_in_wall[Y] && !is_in_wall[X]
		&& !__is_in_door(game->doors, n_coo[X], coo[Y])
		&& !__is_in_door(game->doors, coo[X], n_coo[Y]))
	{
		if (fabsf(coo[X] - (int)n_coo[X]) > fabsf(coo[Y] - (int)n_coo[Y]))
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
		colision_doors(game->doors, coo, p_delta, is_in_wall);
}

__attribute__((flatten))
void	check_colisions(const float p_coo[2], float p_delta[2],
	char *map[], const t_game *game)
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
