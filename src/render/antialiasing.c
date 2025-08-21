/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:35:10 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/21 18:29:01 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define BASE_COEF	10

__attribute__((always_inline))
static inline void	add_clr(const int condition, const t_clr *clr,
	uint64_t sum[3], uint64_t *pcoef, uint64_t coef)
{
	if (condition)
	{
		sum[R] += clr->s_mask.r * coef;
		sum[G] += clr->s_mask.g * coef;
		sum[B] += clr->s_mask.b * coef;
		*pcoef += coef;
	}
}

# define RANGE_ANTIALIASING 3

__attribute__((always_inline))
static inline t_clr	get_avr(const int x, const int y, const t_img img)
{
	const t_clr	*base_pxl = &img.p_data[x + y * img.width];
	const int	i_width = img.width;
	uint64_t	sum[3];
	uint64_t	coef;

	sum[R] = base_pxl->s_mask.r * BASE_COEF;
	sum[G] = base_pxl->s_mask.g * BASE_COEF;
	sum[B] = base_pxl->s_mask.b * BASE_COEF;
	coef = BASE_COEF;
	for (int dx = -RANGE_ANTIALIASING; dx <= RANGE_ANTIALIASING; ++dx)
	{
		for (int dy = -RANGE_ANTIALIASING; dy <= RANGE_ANTIALIASING; ++dy)
			add_clr(x + dx >= 0 && x + dx < i_width
				&& y + dy >= 0 && y + dy < W_HEIGHT,
				&base_pxl[dx + dy * i_width], sum, &coef, 2 * RANGE_ANTIALIASING - abs(dx) - abs(dy));

	}
	// add_clr(x > 0, &base_pxl[-1], sum, &coef);
	// add_clr(x + 1 < i_width, &base_pxl[1], sum, &coef);
	// add_clr(y > 0, &base_pxl[-i_width], sum, &coef);
	// add_clr(y + 1 < img.height, &base_pxl[i_width], sum, &coef);
	// if (!x)
	// 	coef++;
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

void	antialiasing(t_render *render)
{
	const t_img	pre_aa = render->img;
	t_clr		*post_aa;
	int			x;
	int			y;
	int			y_w;

	post_aa = render->img_paa.p_data;
	y = 0;
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
}
