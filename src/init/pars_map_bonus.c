/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:23:06 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/30 18:37:24 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

__attribute__((always_inline))
static inline t_err	__check_one_door(char *map[], const int x,
	const int y, t_pars *pars)
{
	if (map[y][x - 1] == map[y][x + 1]
		&& map[y - 1][x] == map[y + 1][x]
		&& map[y][x - 1] != map[y - 1][x])
	{
		if (!find_door(pars->doors, x + 1, y)
			&& !find_door(pars->doors, x - 1, y)
			&& !find_door(pars->doors, x, y + 1)
			&& !find_door(pars->doors, x, y - 1))
			return (pars->error = NO_ERR);
		pars->error = DOOR_NEXT_TO_DOOR;
	}
	else
		pars->error = INVALID_DOOR;
	ft_strlcpy(pars->err_context, "(", sizeof(pars->err_context));
	ft_lutoacpy(pars->err_context + ft_strlen(pars->err_context), x,
		sizeof(pars->err_context) - ft_strlen(pars->err_context));
	ft_strlcat(pars->err_context, ", ", sizeof(pars->err_context));
	ft_lutoacpy(pars->err_context + ft_strlen(pars->err_context), y,
		sizeof(pars->err_context) - ft_strlen(pars->err_context));
	ft_strlcat(pars->err_context, ")", sizeof(pars->err_context));
	return (pars->error);
}

t_err	check_doors(t_pars *pars)
{
	t_one_door	one_door;	
	uint32_t	i;

	i = 0;
	while (i < N_HASH_DOORS)
	{
		one_door = pars->doors[i];
		if (one_door)
		{
			pars->any_doors = 1;
			if (!pars->door_texture.p_img)
				return (ft_strlcpy(pars->err_context, "Door",
						sizeof(pars->err_context)),
					pars->error = MISSING_TEXTURE);
		}
		while (one_door)
		{
			if (__check_one_door(pars->resized_map,
					one_door->x, one_door->y, pars))
				return (pars->error);
			one_door = one_door->next;
		}
		++i;
	}
	return (NO_ERR);
}

uint32_t	pars_map_bonus(t_pars *pars)
{
	if (pars->rd.flags & R_DONE)
		return (pars->error = MISSING_MAP);
	if (read_map(pars, MAP_CHARS""MAP_CHARS_BNS))
		return (pars->error || pars->error);
	if (count_players(pars, pars->map, pars->dim))
		return (pars->error || pars->error);
	if (flood_fill(pars, pars->map, pars->dim))
		return (pars->error || pars->error);
	if (check_doors(pars))
		return (pars->error || pars->error);
	return (pars->error || pars->error);
}
