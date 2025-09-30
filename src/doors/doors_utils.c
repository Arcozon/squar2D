/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:21:24 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/30 12:59:11 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	hash_door(const int a, const int b)
{
	int	xor;

	xor = PRIME_HASH_DOOR;
	xor ^= (a + b) * PRIME_HASH_DOOR;
	return (xor & (N_HASH_DOORS - 1));
}

t_one_door	new_door(const int x, const int y)
{
	t_one_door	new;

	new = ft_calloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->x = x;
	new->y = y;
	new->closed_percent = VALUE_DOOR_CLOSED;
	new->e_status = D_IDLE;
	new->e_or = D_OR_VER;
	return (new);
}

t_err	add_door(t_doors doors, const int x, const int y)
{
	t_one_door	*the_door;

	the_door = &doors[hash_door(x, y)];
	while (*the_door)
		the_door = &((*the_door)->next);
	*the_door = new_door(x, y);
	if (!the_door)
		return (E_MLC);
	return (NO_ERR);
}

__attribute__((const))
t_one_door	find_door(const t_doors doors, const int x, const int y)
{
	const uint32_t	hash = hash_door(x, y);
	t_one_door		onedoor;

	onedoor = doors[hash];
	while (onedoor)
	{
		if (onedoor->x == x && onedoor->y == y)
			return (onedoor);
		onedoor = onedoor->next;
	}
	return (onedoor);
}
