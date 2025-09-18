/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:06:17 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/18 17:36:17 by gaeudes          ###   ########.fr       */
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
