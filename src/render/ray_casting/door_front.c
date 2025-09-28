/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_front.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 04:48:07 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/28 05:13:19 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

__attribute__((always_inline, flatten, const))
enum e_hit	only_chech_door_edge(t_ray *ray, t_c_door door)
{
	const float	s_c = ray->sin_t / ray->cos_t;
	const float	c_s = ray->cos_t / ray->sin_t;

	fprintf(stderr, "\n");
	DEBUG("DX %f", (ray->f_coo[Y] - (int)(ray->f_coo[Y]) - door->closed_percent) * c_s);
	DEBUG("NX %f", ray->f_coo[X] + (ray->f_coo[Y] - (int)(ray->f_coo[Y]) - door->closed_percent) * c_s);
	if (door->e_or == D_OR_VER)
	{
		if (ray->f_coo[Y] - ray->dir[X] * s_c < door->closed_percent + door->y)
		{
			DEBUG("Ray Coo %f %f", ray->f_coo[X], ray->f_coo[Y])
			DEBUG("DY %f %f", ray->f_coo[Y], (ray->f_coo[Y] - (int)(ray->f_coo[Y])))
			DEBUG("DX %f", (ray->f_coo[Y] - (int)(ray->f_coo[Y]) - door->closed_percent) * c_s);
			ray->f_coo[X] += (ray->f_coo[Y] - (int)(ray->f_coo[Y])
					- door->closed_percent) * c_s;
			ray->f_coo[Y] = (int)ray->f_coo[Y] + door->closed_percent;
			ray->percent = ray->f_coo[X] - (int)ray->f_coo[X];
			DEBUG("R %f %f", ray->f_coo[X], ray->f_coo[Y])
			DEBUG("%d %d %d", ray->add_thing[X], ray->dir[X], ray->for_check[X]);
			DEBUG("%d %d %d", ray->add_thing[Y], ray->dir[Y], ray->for_check[Y]);
			if (ray->f_coo[X] < 31.f || ray->f_coo[X] > 32.f)
			{
				exit(1);
				// WAIT;
			}
			return (ray->hit = door_hor_hit);
		}
	}
	else if (ray->f_coo[X] - ray->dir[Y] * c_s < door->closed_percent + door->x)
	{
		ray->f_coo[Y] += (ray->f_coo[X] - (int)(ray->f_coo[X])
				- door->closed_percent) * s_c;
		ray->f_coo[X] = (int)ray->f_coo[X] + door->closed_percent;
		ray->percent = 1 - (ray->f_coo[Y] - (int)ray->f_coo[Y]);
		return (ray->hit = door_hor_hit);
	}
	return (no_hit);
}
