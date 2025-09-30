/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:06:17 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/30 13:02:29 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

__attribute__((always_inline, const))
static inline int	_i_check_one_corner(t_c_door door,
	const float p_coo_x, const float p_coo_y)
{
	if (door->e_or == D_OR_HOR)
	{
		return ((p_coo_x >= (float)door->x)
			&& (p_coo_x <= door->x + door->closed_percent)
			&& (p_coo_y > (float)door->y)
			&& (p_coo_y < (float)door->y + 1.f));
	}
	else
	{
		return ((p_coo_x > (float)door->x)
			&& (p_coo_x < (float)door->x + 1.f)
			&& (p_coo_y >= (float)door->y)
			&& (p_coo_y <= door->y + door->closed_percent));
	}
}

__attribute__((always_inline, const))
static inline int	_i_is_player_in_door(t_c_door one_door, const float p_coo[2])
{
	return (
		_i_check_one_corner(one_door, p_coo[X] + HALF_P_SIZE,
			p_coo[Y] + HALF_P_SIZE)
		|| _i_check_one_corner(one_door, p_coo[X] + HALF_P_SIZE,
			p_coo[Y] - HALF_P_SIZE)
		|| _i_check_one_corner(one_door, p_coo[X] - HALF_P_SIZE,
			p_coo[Y] + HALF_P_SIZE)
		|| _i_check_one_corner(one_door, p_coo[X] - HALF_P_SIZE,
			p_coo[Y] - HALF_P_SIZE)
	);
}

__attribute__((flatten))
void	__handle_one_door(t_one_door onedoor, t_game *game)
{
	if (onedoor->e_status == D_CLOSING)
	{
		onedoor->closed_percent += DOOR_SPEED;
		if (_i_is_player_in_door(onedoor, game->p_coo))
			onedoor->closed_percent -= DOOR_SPEED;
		if (onedoor->closed_percent >= VALUE_DOOR_CLOSED)
		{
			onedoor->e_status = D_IDLE;
			onedoor->closed_percent = VALUE_DOOR_CLOSED;
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
}

__attribute__((flatten))
void	handle_doors(t_doors doors, t_game *game)
{
	call_all_doors(doors, game, __handle_one_door);
}

__attribute__((flatten))
void	call_all_doors(t_doors doors, t_game *game,
	void (*fct_door)(t_one_door, t_game *))
{
	t_one_door	onedoor;
	uint32_t	i;

	if (game && !game->any_doors)
		return ;
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
