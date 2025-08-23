/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:35:10 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/23 15:11:27 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define BASE_COEF	5
#define RANGE_ANTIALIASING 1

__attribute__((always_inline))
static inline int	ft_abs(const int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

__attribute__((always_inline))
static inline void	loop_around_plx(const int coo_plx[2], const t_clr *plx,
	uint64_t sum[3], uint64_t *pcoef)
{
	int	coef;
	int	x_end;
	int	y_end;
	int	x_i_save;
	int	x_i;
	int	y_i;

	x_end = RANGE_ANTIALIASING;
	if (coo_plx[X] + RANGE_ANTIALIASING >= W_WIDTH)
		x_end = W_WIDTH - coo_plx[X] - 1;
	y_end = RANGE_ANTIALIASING;
	if (coo_plx[Y] + RANGE_ANTIALIASING >= W_HEIGHT)
		y_end = W_HEIGHT - coo_plx[Y] - 1;
	x_i_save = -RANGE_ANTIALIASING;
	if (coo_plx[X] < RANGE_ANTIALIASING)
		x_i_save = -coo_plx[X];
	y_i = -RANGE_ANTIALIASING;
	if (coo_plx[Y] < RANGE_ANTIALIASING)
		y_i = -coo_plx[Y];
	while (y_i <= y_end)
	{
		x_i = x_i_save;
		while (x_i <= x_end)
		{
			coef = 2 * RANGE_ANTIALIASING - ft_abs(x_i) - ft_abs(y_i) + 1;
			sum[R] += plx[x_i + y_i * W_WIDTH].s_mask.r * coef;
			sum[G] += plx[x_i + y_i * W_WIDTH].s_mask.g * coef;
			sum[B] += plx[x_i + y_i * W_WIDTH].s_mask.b * coef;
			*pcoef += coef;
			++x_i;
		}
		++y_i;
	}
}

// __attribute__((always_inline))
// static inline void	add_clr(const int condition, const t_clr *clr,
// 	uint64_t sum[3], uint64_t *pcoef, uint64_t coef)
// {
// 	if (condition)
// 	{
// 		sum[R] += clr->s_mask.r * coef;
// 		sum[G] += clr->s_mask.g * coef;
// 		sum[B] += clr->s_mask.b * coef;
// 		*pcoef += coef;
// 	}
// }


__attribute__((always_inline))
static inline t_clr	get_avr(const int x, const int y, const t_img img)
{
	const t_clr	*base_pxl = &img.p_data[x + y * img.width];
	// const int	i_width = img.width;
	uint64_t	sum[3];
	uint64_t	coef;

	sum[R] = base_pxl->s_mask.r * BASE_COEF;
	sum[G] = base_pxl->s_mask.g * BASE_COEF;
	sum[B] = base_pxl->s_mask.b * BASE_COEF;
	coef = BASE_COEF;

	// for (int dx = -RANGE_ANTIALIASING; dx <= RANGE_ANTIALIASING; ++dx)
	// {
	// 	for (int dy = -RANGE_ANTIALIASING; dy <= RANGE_ANTIALIASING; ++dy)
	// 		add_clr(x + dx >= 0 && x + dx < i_width
	// 			&& y + dy >= 0 && y + dy < W_HEIGHT,
	// 			&base_pxl[dx + dy * i_width], sum, &coef, 2 * RANGE_ANTIALIASING - abs(dx) - abs(dy));

	// }
	loop_around_plx((const int [2]){x, y}, base_pxl, sum, &coef);
	sum[R] /= coef;
	sum[G] /= coef;
	sum[B] /= coef;
	// if ((sum[R] << 2 * __CHAR_BIT__ | sum[G] << __CHAR_BIT__ | sum[B]) != 0x102ff)
	// {
	// 	DEBUG("%lx", (sum[R] << 2 * __CHAR_BIT__ | sum[G] << __CHAR_BIT__ | sum[B]))
	// 	WAIT
	// }
	return ((t_clr){.rgb = (sum[R] << 2 * __CHAR_BIT__
			| sum[G] << __CHAR_BIT__ | sum[B])});
}

# include "time.h"

void	antialiasing(t_render *render)
{
	const t_img	pre_aa = render->img;
	t_clr		*post_aa;
	int			x;
	int			y;
	int			y_w;

	post_aa = render->img_paa.p_data;
	y = 0;
	DEBUG("START")
	clock_t start = clock();
	/*Do something*/
	
	while (y < W_HEIGHT)
	{
		y_w = y * W_WIDTH;
		x = 0;
		while (x < W_WIDTH)
		{
			post_aa[y_w + x] = get_avr(x, y, pre_aa);
			// DEBUG("[%d|%d]%.6x", x, y, post_aa[y_w + x].rgb)
			// WAIT
			++x;
		}
		++y;
	}
	clock_t end = clock();
	DEBUG("END %f" ,(float)(end - start) / CLOCKS_PER_SEC)
}
