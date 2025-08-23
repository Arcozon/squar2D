/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_floor_ceiling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:24:00 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/23 17:38:49 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_floor_ceiling(t_render *render)
{
	const uint64_t	half_size = render->img.height * render->img.width / 2;
	const t_clr		c_clr = render->c_clr;
	const t_clr		f_clr = render->f_clr;

	ft_clrset(render->img.p_data, c_clr, half_size);
	ft_clrset(render->img.p_data + half_size, f_clr, half_size);
}
