/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_front.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 04:48:07 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/30 12:48:18 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

__attribute__((always_inline, flatten, const))
enum e_hit	only_chech_door_edge(t_ray *ray, t_c_door door)
{
	const float	s_c = ray->sin_t / ray->cos_t;
	const float	c_s = ray->cos_t / ray->sin_t;
	const float	d_x = ray->f_coo[X] - (int)ray->f_coo[X];
	const float	d_y = ray->f_coo[Y] - (int)ray->f_coo[Y];

	if (door->e_or == D_OR_VER)
	{
		if (ray->f_coo[Y] + s_c * (d_x - ray->add_thing[X])
			< door->closed_percent + door->y)
		{
			ray->f_coo[X] += (d_y - door->closed_percent) * c_s;
			ray->f_coo[Y] = (int)ray->f_coo[Y] + door->closed_percent;
			ray->percent = ray->f_coo[X] - (int)ray->f_coo[X];
			return (ray->hit = door_hor_hit);
		}
	}
	else if (ray->f_coo[X] + c_s * (d_y - ray->add_thing[Y])
		< door->closed_percent + door->x)
	{
		ray->f_coo[Y] += (d_x - door->closed_percent) * s_c;
		ray->f_coo[X] = (int)ray->f_coo[X] + door->closed_percent;
		ray->percent = 1 - (ray->f_coo[Y] - (int)ray->f_coo[Y]);
		return (ray->hit = door_hor_hit);
	}
	return (no_hit);
}
