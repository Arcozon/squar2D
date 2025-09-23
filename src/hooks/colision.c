/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colision.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:50:55 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/23 11:35:58 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

__attribute__((always_inline, pure, const))
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
	const float coo[2], float p_delta[2])
{
	const float	n_coo[2] = {coo[X] + p_delta[X], coo[Y] + p_delta[Y]};
	const int	crossed[2] = {(int)coo[X] != (int)n_coo[X],
		(int)coo[Y] != (int)n_coo[Y]};
	const int	is_in_wall[2] = {map[(int)coo[Y]][(int)n_coo[X]] == WALL_CHAR,
		map[(int)n_coo[Y]][(int)coo[X]] == WALL_CHAR};

	if (crossed[X] && crossed[Y]
		&& map[(int)n_coo[Y]][(int)n_coo[X]] == WALL_CHAR
		&& !is_in_wall[Y] && !is_in_wall[X])
	{
		p_delta[X] = __get_new_delta(coo[X], n_coo[X], p_delta[X] < 0);
		p_delta[Y] = __get_new_delta(coo[Y], n_coo[Y], p_delta[Y] < 0);
	}
	else
	{
		if (crossed[X] && is_in_wall[X])
			p_delta[X] = __get_new_delta(coo[X], n_coo[X], p_delta[X] < 0);
		if (crossed[Y] && is_in_wall[Y])
			p_delta[Y] = __get_new_delta(coo[Y], n_coo[Y], p_delta[Y] < 0);
	}
}

__attribute__((flatten))
void	check_colisions(const float p_coo[2], float p_delta[2], char *map[])
{
	const float	coo_nw[2] = {p_coo[X] - HALF_P_SIZE, p_coo[Y] - HALF_P_SIZE};
	const float	coo_ne[2] = {p_coo[X] + HALF_P_SIZE, p_coo[Y] - HALF_P_SIZE};
	const float	coo_se[2] = {p_coo[X] + HALF_P_SIZE, p_coo[Y] + HALF_P_SIZE};
	const float	coo_sw[2] = {p_coo[X] - HALF_P_SIZE, p_coo[Y] + HALF_P_SIZE};

	if (p_delta[X] < 0)
	{
		if (p_delta[Y] < 0)
			__check_one_col(map, coo_nw, p_delta);
		else
			__check_one_col(map, coo_sw, p_delta);
	}
	else
	{
		if (p_delta[Y] < 0)
			__check_one_col(map, coo_ne, p_delta);
		else
			__check_one_col(map, coo_se, p_delta);
	}
	__check_one_col(map, coo_ne, p_delta);
	__check_one_col(map, coo_nw, p_delta);
	__check_one_col(map, coo_sw, p_delta);
	__check_one_col(map, coo_se, p_delta);
}
