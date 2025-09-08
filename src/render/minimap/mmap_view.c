/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmap_view.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:05:53 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/08 15:03:33 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

__attribute__((always_inline))
static inline int	ft_abs(const int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

void	render_line(float start[2], const int end[2], t_img mmap)
{
	const int	nstep = ft_abs(start[X] - end[X])
		+ ft_abs(start[Y] - end[Y]) + 1;
	const float	step[2] = {
		(end[X] - start[X]) / (float)nstep,
		(end[Y] - start[Y]) / (float)nstep};
	int			i;

	i = 0;
	while (i < nstep)
	{
		mmap.p_data[(int)start[Y] * MMAP_WIDHT + (int)start[X]].rgb
			= MMAP_CLR_VIEW;
		start[X] += step[X];
		start[Y] += step[Y];
		++i;
	}
}

__attribute__((always_inline))
static inline void	__bound_ray_to_screen(float end_ray[2], const t_ray ray,
	const int map_pcoo[2], const float p_coo[2])
{
	if (end_ray[X] < 0 || end_ray[X] >= MMAP_WIDHT)
	{
		if (end_ray[X] < 0)
			end_ray[X] = 0;
		else
			end_ray[X] = MMAP_WIDHT - 1;
		end_ray[Y] = (ray.f_coo[Y] - p_coo[Y]) * MMAP_SQUARE_SIZE;
		end_ray[Y] *= (end_ray[X] - map_pcoo[X])
			/ ((ray.f_coo[X] - p_coo[X]) * MMAP_SQUARE_SIZE);
		end_ray[Y] += map_pcoo[Y];
	}
	if (end_ray[Y] < 0 || end_ray[Y] >= MMAP_HEIGHT)
	{
		if (end_ray[Y] < 0)
			end_ray[Y] = 0;
		else
			end_ray[Y] = MMAP_HEIGHT - 1;
		end_ray[X] = (ray.f_coo[X] - p_coo[X]) * MMAP_SQUARE_SIZE;
		end_ray[X] *= (end_ray[Y] - map_pcoo[Y])
			/ ((ray.f_coo[Y] - p_coo[Y]) * MMAP_SQUARE_SIZE);
		end_ray[X] += map_pcoo[X];
	}
}

__attribute__((flatten))
void	render_mmap_one_ray(t_game *game, const t_ray ray)
{
	static const int	map_pcoo[2] = {MMAP_WIDHT / 2, MMAP_HEIGHT / 2};
	float				end_ray[2];

	end_ray[X] = map_pcoo[X]
		+ (ray.f_coo[X] - game->p_coo[X]) * MMAP_SQUARE_SIZE;
	end_ray[Y] = map_pcoo[Y]
		+ (ray.f_coo[Y] - game->p_coo[Y]) * MMAP_SQUARE_SIZE;
	__bound_ray_to_screen(end_ray, ray, map_pcoo, game->p_coo);
	render_line(end_ray, map_pcoo, game->render.img_mmap);
}
