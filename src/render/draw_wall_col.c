/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_col.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 12:39:45 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/06 15:12:26 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define V_FOV M_PI_4

__attribute__((always_inline))
static inline void	_fill_dcwall(t_dcwall *info, const float dist_0, const int img_height)
{
	info->x_img = (int)(info->img_percent * info->wall_img.width);
	// if (info->distance == 0.f)
	// 	info->screen_y_range = W_HEIGHT * 10;
	// else
		info->screen_y_range = (int)(W_HEIGHT / (2 * info->distance / dist_0));
	if (info->screen_y_range > W_HEIGHT)
	{
		info->img_y_range = (img_height * (int)(info->screen_y_range / (float)W_HEIGHT));
		info->img_y_start = (img_height - info->img_y_range) / 2;
		info->screen_y_start = 0;
		info->screen_y_range = W_HEIGHT;
	}
	else
	{
		info->img_y_start = 0;
		info->img_y_range = img_height;
		info->screen_y_start = (W_HEIGHT - info->screen_y_range) / 2;
	}
	// DEBUG("DISTANCE: %f", info->distance)
	// DEBUG("SCREEN: (x, [%d|%d])", info->screen_y_start, info->screen_y_start + info->screen_y_range)
	// DEBUG("IMG: (x, [%d|%d])", info->img_y_start, info->img_y_start + info->img_y_range)
}

__attribute__((always_inline))
static inline void	_draw_col_wall(const t_dcwall info, uint32_t screenX[], const uint32_t wallX[], const int wallWidth)
{
	const float	step_wall = info.img_y_range / (info.screen_y_range + 1);
	float		i_wall;
	int			i;

	i_wall = 0;
	i = 0;
	// DEBUG("STEP: %f", step_wall)
	// WAIT
	while (i < info.screen_y_range)
	{
		// DEBUG("i: %d | iW: %d", i, (int)i_wall)
		screenX[i * W_WIDTH] = wallX[((int)i_wall) * wallWidth];
		i_wall += step_wall;
		++i;
	}
}

__attribute__((flatten))
void	draw_col_wall(t_dcwall info, t_img screen_img, const int screen_x, t_img wall_img)
{
	const float	dist_0 = fabs(tanf(M_PI_4 - (V_FOV / 2)));

	_fill_dcwall(&info, dist_0, wall_img.height);
	_draw_col_wall(info, (uint32_t *)&screen_img.p_data[screen_x + screen_img.width * info.screen_y_start],
		(uint32_t *)&wall_img.p_data[info.x_img + wall_img.width * info.img_y_start], wall_img.width);
}
