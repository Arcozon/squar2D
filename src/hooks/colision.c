/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colision.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:50:55 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/08 17:55:10 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


// __attribute__((always_inline))
// void	init_one_col(const float start[2], const float p_delta[2], t_col *col,
// 	const int offset[2])
// {
// 	col->start_coo[X] = start[X] + offset[X] * HALF_P_SIZE;
// 	col->start_coo[Y] = start[Y] + offset[Y] * HALF_P_SIZE;
// 	col->coo[X] = col->start_coo[X];
// 	col->coo[Y] = col->start_coo[Y];
// 	col->p_delta[X] = p_delta[X];
// 	col->p_delta[Y] = p_delta[Y];
// 	col->tt_nstep[X] = 0.f;
// 	col->tt_nstep[Y] = 0.f;
// 	col->to_add[X] = 0;
// 	col->dir[X] = -1;
// 	if (p_delta[X] > 0)
// 	{
// 		col->dir[X] = 1;
// 		col->to_add[X] = 1;
// 	}
// 	col->to_add[Y] = 0;
// 	col->dir[Y] = 1;
// 	if (p_delta[Y] < 0)
// 	{
// 		col->dir[Y] = -1;
// 		col->to_add[Y] = 1;
// 	}
// 	col->hit = 0;
// 	col->done = 0;
// 	col->ratio2[X] = 0;
// 	if (col->p_delta[Y] < -ZERO_RANGE || col->p_delta[Y] > ZERO_RANGE)
// 		col->ratio2[X] = p_delta[X] / p_delta[Y];
// 	col->ratio2[X] *= col->ratio2[X];
// 	col->ratio2[Y] = 0;
// 	if (col->p_delta[X] < -ZERO_RANGE || col->p_delta[X] > ZERO_RANGE)
// 		col->ratio2[Y] = p_delta[Y] / p_delta[X];
// 	col->ratio2[Y] *= col->ratio2[Y];
// }

// __attribute__((always_inline))
// int	check_one_colision(t_col *col, char *map[])
// {
// 	DEBUG("COO %f %f", col->coo[X], col->coo[Y])
// 	while (!col->done && (!col->hit[X] || !col->hit[Y]))
// 	{
// 		col->n_step[X] = ((int)col->coo[X] + col->to_add[X]) - col->coo[X];
// 		if (col->n_step[X] == 0.f)
// 			col->n_step[X] = col->dir[X];
// 		col->n_step[Y] = ((int)col->coo[Y] + col->to_add[Y]) - col->coo[Y];
// 		if (col->n_step[Y] == 0)
// 			col->n_step[Y] = col->dir[Y];
// 		col->dist_n_step_2[X] = col->n_step[X] * col->n_step[X] * (1 + col->ratio2[Y]);
// 		DEBUG("rX2 %f", col->ratio2[X])
// 		DEBUG("sX: %f, dX %f", col->n_step[X], col->dist_n_step_2[X])
// 		col->dist_n_step_2[Y] = col->n_step[Y] * col->n_step[Y] * (1 + col->ratio2[X]);
// 		DEBUG("rY2 %f", col->ratio2[Y])
// 		DEBUG("sY: %f, dY %f", col->n_step[Y], col->dist_n_step_2[Y])
// 		WAIT
// 		// DEBUG("X[%f] [%f|%d] %f", col->p_delta[X], col->coo[X], (int)col->coo[X] + col->to_add[X], col->n_step[X])
// 		// DEBUG("Y[%f] [%f|%d] %f", col->p_delta[Y], col->coo[Y], (int)col->coo[Y] + col->to_add[Y], col->n_step[Y])
// 		col->done = 1;
// 		if (col->dist_n_step_2[X] <= col->dist_n_step_2[Y] && fabs(col->tt_nstep[X]) + fabs(col->n_step[X]) <= fabs(col->p_delta[X]))
// 		{
// 			col->done = 0;
// 			DEBUG("Xcheck %d %d", (int)col->coo[X] + col->dir[X], (int)col->coo[Y])
// 			if (map[(int)col->coo[Y]][(int)col->coo[X] + col->dir[X]] == WALL_CHAR)
// 			{
// 				DEBUG("Xcol")
// 				col->hit[X] = 1;
// 			}
// 			col->tt_nstep[X] += col->n_step[X];
// 			col->coo[X] += col->n_step[X];
// 			DEBUG("COO %f %f", col->coo[X], col->coo[Y])
// 		}
// 		else if (fabs(col->tt_nstep[Y]) + fabs(col->n_step[Y]) <= fabs(col->p_delta[Y]))
// 		{
// 			col->done = 0;
// 			DEBUG("Ycheck %d %d", (int)col->coo[X], (int)col->coo[Y] + col->dir[Y])
// 			if (map[(int)col->coo[Y] + col->dir[Y]][(int)col->coo[X]] == WALL_CHAR)
// 			{
// 				DEBUG("Ycol")
// 				col->hit[Y] = 1;
// 			}
// 			col->tt_nstep[Y] += col->n_step[Y];
// 			col->coo[Y] += col->n_step[Y];
// 		}
// 		WAIT
// 	}
// 	DEBUG("DONE")
// 	return (1);
// 	(void)map;
// }

__attribute__((flatten))
void	check_colisions(const float p_coo[2], float p_delta[2], char *map[])
{
	// t_col	col;

	// p_delta[X] = 3;
	// p_delta[Y] = 2;
	// // init_one_col(p_coo, p_delta, &col, (int []){1, 1});
	// init_one_col(p_coo, p_delta, &col, (int []){0, 0});
	// if (check_one_colision(&col, map))
	// {
	// 	p_delta[X] = col.start_coo[X] - col.coo[X];
	// }
	// init_one_col(p_coo, p_delta, &col, (int []){1, -1});
	// init_one_col(p_coo, p_delta, &col, (int []){-1, 1});
	// init_one_col(p_coo, p_delta, &col, (int []){-1, -1});
	(void)p_coo, (void)p_delta, (void)map;
}
