/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:06:17 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/18 15:32:32 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	__handle_one_door(t_one_door onedoor)
{
	if (onedoor->e_status == D_CLOSING)
	{
		onedoor->open = 0;
		onedoor->closed_percent += DOOR_SPEED;
		if (onedoor->closed_percent >= VALUE_CLOSED)
		{
			onedoor->e_status = D_IDLE;
			onedoor->closed_percent =VALUE_CLOSED;
		}
	}
	else if (onedoor->e_status == D_OPENING)
	{
		onedoor->closed_percent -= DOOR_SPEED;
		if (onedoor->closed_percent <= VALUE_OPEN)
		{
			onedoor->open = 1;
			onedoor->e_status = D_IDLE;
			onedoor->closed_percent = VALUE_OPEN;
		}
	}
	else
	{
		if (onedoor->closed_percent == VALUE_OPEN)
			onedoor->e_status = D_CLOSING;
		else
			onedoor->e_status = D_OPENING;
	}
}

__attribute__((flatten))
void	handle_doors(t_doors doors)
{
	t_one_door	onedoor;
	uint32_t	i;

	i = 0;
	while (i < N_HASH_DOORS)
	{
		onedoor = doors[i];
		while (onedoor)
		{
			__handle_one_door(onedoor);
			onedoor = onedoor->next;
		}
		++i;
	}
}
