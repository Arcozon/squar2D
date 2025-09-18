/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:06:17 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/18 16:56:33 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	__handle_one_door(t_one_door onedoor, t_game *game)
{
	if (onedoor->e_status == D_CLOSING)
	{
		onedoor->closed_percent += DOOR_SPEED;
		if (onedoor->closed_percent >= VALUE_DOOR_CLOSED)
		{
			onedoor->e_status = D_IDLE;
			onedoor->closed_percent =VALUE_DOOR_CLOSED;
		}
	}
	else if (onedoor->e_status == D_OPENING)
	{
		onedoor->closed_percent -= DOOR_SPEED;
		if (onedoor->closed_percent <= VALUE_DOOR_OPEN)
		{
			onedoor->e_status = D_IDLE;
			onedoor->closed_percent = VALUE_DOOR_OPEN;
		}
	}
	// else
	// {
	// 	if (onedoor->closed_percent == VALUE_DOOR_OPEN)
	// 		onedoor->e_status = D_CLOSING;
	// 	else
	// 		onedoor->e_status = ((void)game, D_OPENING);
	// }
	(void)game;
}

__attribute__((flatten))
void	handle_doors(t_doors doors)
{
	call_all_doors(doors, 0, __handle_one_door);
}


__attribute__((flatten))
void	call_all_doors(t_doors doors, t_game *game,
	void (*fct_door)(t_one_door, t_game *))
{
	t_one_door	onedoor;
	uint32_t	i;

	i = 0;
	while (i < N_HASH_DOORS)
	{
		onedoor = doors[i];
		while (onedoor)
		{
			fct_door(onedoor, game);
			onedoor = onedoor->next;
		}
		++i;
	}
}

__attribute__((always_inline, const))
float	distance2_door(const float p_coo[2],
	const float door_x, const float door_y)
{
	const float d_x = p_coo[X] - door_x;
	const float d_y = p_coo[Y] - door_y;

	return (d_x * d_x + d_y * d_y);
}

t_one_door	find_closest_door(t_doors doors, const float p_coo[2])
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
