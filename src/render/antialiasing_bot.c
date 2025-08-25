/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing_bot.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:32:25 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/25 16:27:57 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// returns X, bounded to [min, max[ (max excluded)
__attribute__((always_inline, pure, const))
static inline int	ft_bound(const int x, const int min, const int max)
{
	if (x < min)
		return (min);
	if (x >= max)
		return (max - 1);
	return (x);
}

__attribute__((always_inline, pure, const))
static inline int	ft_abs(const int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

__attribute__((always_inline))
static inline uint64_t	loop_around_plx(const int coo_plx[2], const t_clr *plx,
	uint64_t sum[3], const uint64_t range)
{
	const int	x_end = ft_bound(range, -coo_plx[X], W_WIDTH - coo_plx[X]);
	const int	x_i_save = ft_bound(-range, -coo_plx[X], W_WIDTH - coo_plx[X]);
	const int	y_end = ft_bound(range, -coo_plx[Y], W_HEIGHT - coo_plx[Y]);
	int			coef[2];
	int			i[2];

	coef[0] = BASE_COEF;
	i[Y] = ft_bound(-range, -coo_plx[Y], W_HEIGHT - coo_plx[Y]);
	while (i[Y] <= y_end)
	{
		i[X] = x_i_save;
		while (i[X] <= x_end)
		{
			coef[1] = 2 * range - ft_abs(i[X]) - ft_abs(i[Y]) + 1;
			sum[R] += plx[i[X] + i[Y] * W_WIDTH].s_mask.r * coef[1];
			sum[G] += plx[i[X] + i[Y] * W_WIDTH].s_mask.g * coef[1];
			sum[B] += plx[i[X] + i[Y] * W_WIDTH].s_mask.b * coef[1];
			coef[0] += coef[1];
			++i[X];
		}
		++i[Y];
	}
	return (coef[0]);
}

__attribute__((always_inline))
static inline t_clr	get_avr(const int coo[2],
	const t_clr *pre_plx, const int range)
{
	uint64_t	sum[3];
	uint64_t	coef;

	sum[R] = pre_plx->s_mask.r * BASE_COEF;
	sum[G] = pre_plx->s_mask.g * BASE_COEF;
	sum[B] = pre_plx->s_mask.b * BASE_COEF;
	coef = loop_around_plx(coo, pre_plx, sum, range);
	sum[R] /= coef;
	sum[G] /= coef;
	sum[B] /= coef;
	return ((t_clr){.rgb = (sum[R] << 2 * __CHAR_BIT__
			| sum[G] << __CHAR_BIT__ | sum[B])});
}

__attribute__((flatten))
void	antialiasing_bot(const t_clr pre_aa[],
	t_clr post_aa[], const t_clr f_clr)
{
	int	x;
	int	y;
	int	i;

	x = 0;
	while (x < W_WIDTH)
	{
		y = W_HEIGHT - 1;
		while (y >= 0 && pre_aa[y * W_WIDTH + x].rgb == f_clr.rgb)
			--y;
		i = -RANGE_ANTIALIASING;
		while (i <= RANGE_ANTIALIASING)
		{
			post_aa[(y + i) * W_WIDTH + x] = get_avr((int [2]){x, y + i},
					&pre_aa[(y + i) * W_WIDTH + x],
					RANGE_ANTIALIASING - ft_abs(i) + 1);
			++i;
		}
		++x;
	}
}
