/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_put_img_to_img.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:21:17 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/23 12:40:42 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

__attribute__((always_inline, const))
static inline int	ft_bound(const int a, const int min, const int max)
{
	if (a < min)
		return (min);
	else if (a >= max)
		return (max - 1);
	else
		return (a);
}

__attribute__((flatten))
void	cub_putimgtoimg(const t_img src, t_img dst, const int coo[2])
{
	const int	start[2] = {
		ft_bound(coo[X], 0, dst.width),
		ft_bound(coo[Y], 0, dst.height)};
	const int	end[2] = {
		start[X] + ft_bound(src.width, 0, dst.width - start[X]),
		start[Y] + ft_bound(src.height, 0, dst.height - start[Y])};
	int			ix;
	int			iy;

	iy = start[Y];
	while (iy < end[Y])
	{
		ix = start[X];
		while (ix < end[X])
		{
			dst.p_data[ix + iy * dst.width] = src.p_data[ix + iy * src.width];
			++ix;
		}
		++iy;
	}
}
