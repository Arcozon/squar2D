/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_close_door.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 17:10:10 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/18 17:11:17 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

__attribute__((always_inline, const))
static inline float	distance2_door(const float p_coo[2],
	const float door_x, const float door_y)
{
	const float d_x = p_coo[X] - door_x;
	const float d_y = p_coo[Y] - door_y;

	return (d_x * d_x + d_y * d_y);
}

__attribute__((always_inline))
static inline t_one_door	find_closest_door(t_doors doors, const float p_coo[2])
{
	t_one_door	the_closest;
	t_one_door	onedoor;
	uint32_t	i;
	float		distance2_closest;
	float		distance2_this;

	the_closest = NULL;
	distance2_closest = RADIUS_DOOR_OPEN * RADIUS_DOOR_OPEN;
	i = 0;
	while (i < N_HASH_DOORS)
	{
		onedoor = doors[i++];
		while (onedoor)
		{
			distance2_this = distance2_door(p_coo,
					onedoor->x + 0.5f, onedoor->y + 0.5f);
			if (distance2_this < distance2_closest)
			{
				distance2_closest = distance2_this;
				the_closest = onedoor;
			}
			onedoor = onedoor->next;
		}
	}
	return (the_closest);
}

__attribute__((flatten))
void	open_close_door(t_game *game)
{
	t_one_door	the_one;
	
	the_one = find_closest_door(game->doors, game->p_coo);
	if (!the_one)
		return ;
	if (the_one->e_status == D_CLOSING)
		the_one->e_status = D_OPENING;
	else if (the_one->e_status == D_OPENING)
		the_one->e_status = D_CLOSING;
	else
	{
		if (the_one->closed_percent == VALUE_DOOR_CLOSED)
			the_one->e_status = D_OPENING;
		else
			the_one->e_status = D_CLOSING;
	}
}
