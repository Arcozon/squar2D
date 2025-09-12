/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colision.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:50:55 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/12 12:58:15 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// __attribute__((always_inline))
// static inline void	__check_one_col(char *map[],
// 	const float coo[2], float p_delta[2])
// {
// 	const int	to_add[2] = {(p_delta[X] < 0), (p_delta[Y] < 0)};
// 	const float	n_coo[2] = {coo[X] + p_delta[X], coo[Y] + p_delta[Y]};
// 	const int	crossed[2] = {(int)coo[X] != (int)n_coo[X],
// 		(int)coo[Y] != (int)n_coo[Y]};

// 	if (map[(int)n_coo[Y]][(int)n_coo[X]] == WALL_CHAR)
// 	{
// 		if (crossed[X] && crossed[Y] && 0)
// 		{
// 			p_delta[X] = ((int)n_coo[X] + to_add[X]) - coo[X];
// 			if (!to_add[X])
// 				p_delta[X] -= ZERO_RANGE;
// 			p_delta[Y] = ((int)n_coo[Y] + to_add[Y]) - coo[Y];
// 			if (!to_add[Y])
// 				p_delta[Y] -= ZERO_RANGE;
// 		}
// 		else
// 		if (crossed[X])
// 		{
// 			p_delta[X] = ((int)n_coo[X] + to_add[X]) - coo[X];
// 			if (!to_add[X])
// 				p_delta[X] -= ZERO_RANGE;
// 			else
// 				p_delta[X] += ZERO_RANGE;
// 		}
// 		if (crossed[Y])
// 		{
// 			p_delta[Y] = ((int)n_coo[Y] + to_add[Y]) - coo[Y];
// 			if (!to_add[Y])
// 				p_delta[Y] -= ZERO_RANGE;
// 			else
// 				p_delta[Y] += ZERO_RANGE;
// 		}
// 		else
// 			DEBUG("HOW ?");
// 	}
// }

// __attribute__((always_inline))
// static inline void	__check_one_col(char *map[],
// 	const float coo[2], float p_delta[2])
// {
// 	const int	to_add[2] = {(p_delta[X] < 0), (p_delta[Y] < 0)};
// 	const float	n_coo[2] = {coo[X] + p_delta[X], coo[Y] + p_delta[Y]};
// 	const int	crossed[2] = {(int)coo[X] != (int)n_coo[X],
// 		(int)coo[Y] != (int)n_coo[Y]};
// 	const int	is_in_wall[2] = {map[(int)coo[Y]][(int)n_coo[X]] == WALL_CHAR,
// 					map[(int)n_coo[Y]][(int)coo[X]] == WALL_CHAR};

// 	if (crossed[X] && crossed[Y] && map[(int)n_coo[Y]][(int)n_coo[X]] == WALL_CHAR && !is_in_wall[Y] && !is_in_wall[X])
// 	{
// 		DEBUG("both")
// 		if (is_in_wall[X] && !is_in_wall[Y])
// 		{
// 			p_delta[X] = ((int)n_coo[X] + to_add[X]) - coo[X];
// 			if (!to_add[X])
// 				p_delta[X] -= ZERO_RANGE;
// 		}
// 		else if (is_in_wall[Y] && !is_in_wall[X])
// 		{
// 			p_delta[Y] = ((int)n_coo[Y] + to_add[Y]) - coo[Y];
// 			if (!to_add[Y])
// 				p_delta[Y] -= ZERO_RANGE;
// 		}
// 		else if (is_in_wall[X] && is_in_wall[Y])
// 			DEBUG("CORNERED")
// 		else
// 			DEBUG("NONE")
// 	}
// 	else
// 	{
// 		if (crossed[X] && is_in_wall[X])
// 		{
// 			p_delta[X] = ((int)n_coo[X] + to_add[X]) - coo[X];
// 			if (!to_add[X])
// 				p_delta[X] -= ZERO_RANGE;
// 		}
// 		if (crossed[Y] && is_in_wall[Y])
// 		{
// 			p_delta[Y] = ((int)n_coo[Y] + to_add[Y]) - coo[Y];
// 			if (!to_add[Y])
// 				p_delta[Y] -= ZERO_RANGE;
// 		}
// 	}
// }

__attribute__((always_inline))
static inline void	__check_one_col(char *map[],
	const float coo[2], float p_delta[2])
{
	const int	to_add[2] = {(p_delta[X] < 0), (p_delta[Y] < 0)};
	const float	n_coo[2] = {coo[X] + p_delta[X], coo[Y] + p_delta[Y]};
	const int	crossed[2] = {(int)coo[X] != (int)n_coo[X],
		(int)coo[Y] != (int)n_coo[Y]};
	const int	is_in_wall[2] = {map[(int)coo[Y]][(int)n_coo[X]] == WALL_CHAR,
					map[(int)n_coo[Y]][(int)coo[X]] == WALL_CHAR};

	if (crossed[X] && crossed[Y] && map[(int)n_coo[Y]][(int)n_coo[X]] == WALL_CHAR && !is_in_wall[Y] && !is_in_wall[X])
	{
		p_delta[X] = ((int)n_coo[X] + to_add[X]) - coo[X];
		if (!to_add[X])
			p_delta[X] -= ZERO_RANGE;
		p_delta[Y] = ((int)n_coo[Y] + to_add[Y]) - coo[Y];
		if (!to_add[Y])
			p_delta[Y] -= ZERO_RANGE;
	}
	else
	{
		if (crossed[X] && is_in_wall[X])
		{
			p_delta[X] = ((int)n_coo[X] + to_add[X]) - coo[X];
			if (!to_add[X])
				p_delta[X] -= ZERO_RANGE;
		}
		if (crossed[Y] && is_in_wall[Y])
		{
			p_delta[Y] = ((int)n_coo[Y] + to_add[Y]) - coo[Y];
			if (!to_add[Y])
				p_delta[Y] -= ZERO_RANGE;
		}
	}
}

__attribute__((flatten))
void	check_colisions(const float p_coo[2], float p_delta[2], char *map[])
{
	const float	coo_nw[2] = {p_coo[X] - HALF_P_SIZE, p_coo[Y] - HALF_P_SIZE};
	const float	coo_ne[2] = {p_coo[X] + HALF_P_SIZE, p_coo[Y] - HALF_P_SIZE};
	const float	coo_se[2] = {p_coo[X] + HALF_P_SIZE, p_coo[Y] + HALF_P_SIZE};
	const float	coo_sw[2] = {p_coo[X] - HALF_P_SIZE, p_coo[Y] + HALF_P_SIZE};
	float		s_dlt[2];

	(s_dlt[X] = p_delta[X], s_dlt[Y] = p_delta[Y]);
	__check_one_col(map, coo_nw, p_delta);
	if ((s_dlt[X] != p_delta[X] || s_dlt[Y] != p_delta[Y]) && map[(int)(p_coo[Y] + p_delta[Y])][(int)(p_coo[X] + p_delta[X])] == WALL_CHAR)
	{
		DEBUG("NW: %f | %f", p_delta[X] - s_dlt[X], p_delta[Y] - s_dlt[Y])	;
		WAIT;
	}

	(s_dlt[X] = p_delta[X], s_dlt[Y] = p_delta[Y]);
	__check_one_col(map, coo_ne, p_delta);
	if ((s_dlt[X] != p_delta[X] || s_dlt[Y] != p_delta[Y]) && map[(int)(p_coo[Y] + p_delta[Y])][(int)(p_coo[X] + p_delta[X])] == WALL_CHAR)
	{
		DEBUG("NE: %f | %f", p_delta[X] - s_dlt[X], p_delta[Y] - s_dlt[Y])	;
		WAIT;
	}

	(s_dlt[X] = p_delta[X], s_dlt[Y] = p_delta[Y]);
	__check_one_col(map, coo_se, p_delta);
	if ((s_dlt[X] != p_delta[X] || s_dlt[Y] != p_delta[Y]) && map[(int)(p_coo[Y] + p_delta[Y])][(int)(p_coo[X] + p_delta[X])] == WALL_CHAR)\
	{
		DEBUG("SE: %f | %f", p_delta[X] - s_dlt[X], p_delta[Y] - s_dlt[Y])	;
		WAIT;
	}

	(s_dlt[X] = p_delta[X], s_dlt[Y] = p_delta[Y]);
	__check_one_col(map, coo_sw, p_delta);
	if ((s_dlt[X] != p_delta[X] || s_dlt[Y] != p_delta[Y]) && map[(int)(p_coo[Y] + p_delta[Y])][(int)(p_coo[X] + p_delta[X])] == WALL_CHAR)
	{
		DEBUG("SW: %f | %f", p_delta[X] - s_dlt[X], p_delta[Y] - s_dlt[Y])	;
		WAIT;
	}
}
