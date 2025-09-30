/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_floor_ceiling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:24:00 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/30 13:20:59 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

__attribute__((nonnull, always_inline))
static inline void	__ft_clrset(t_clr *img_data, const t_clr color, const uint64_t size)
{
	uint64_t	i;

	i = 0;
	while (i < size)
	{
		img_data[i] = color;
		++i;
	}
}

void	set_floor_ceiling(t_render *render)
{
	const uint64_t	half_size = render->img.height * render->img.width / 2;
	const t_clr		c_clr = render->c_clr;
	const t_clr		f_clr = render->f_clr;

	__ft_clrset(render->img.p_data, c_clr, half_size);
	__ft_clrset(render->img.p_data + half_size, f_clr, half_size);
}
