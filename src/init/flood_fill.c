/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 16:09:13 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/30 14:49:58 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

__attribute__((hot))
t_err	recursive_shi(char **map,
	const uint64_t dim[2], const uint64_t x, const uint64_t y)
{
	if (x < 0 || x >= dim[X] || y < 0 || y >= dim[Y])
		return (UNCLOSED_MAP);
	if (map[y][x] == VISITED_EMPTY || map[y][x] == WALL_CHAR
		|| map[y][x] == VISITED_DOOR)
		return (NO_ERR);
	if (map[y][x] == CHAR_DOOR)
		map[y][x] = VISITED_DOOR;
	else
		map[y][x] = VISITED_EMPTY;
	if (recursive_shi(map, dim, x - 1, y)
		|| recursive_shi(map, dim, x + 1, y)
		|| recursive_shi(map, dim, x, y - 1)
		|| recursive_shi(map, dim, x, y + 1))
		return (UNCLOSED_MAP);
	return (NO_ERR);
}

__attribute__((always_inline))
static inline void	__get_map_range(char *map[],
	const uint64_t dim[2], int64_t range[2][2], const uint64_t iy)
{
	if (ft_sn_strchr(map[iy], dim[X], VISITED_CHARS) - map[iy]
		< range[X][MINR_MAP])
	{
		range[X][MINR_MAP] = ft_sn_strchr(map[iy], dim[X], VISITED_CHARS)
			- map[iy];
	}
	if (ft_sn_strrchr(map[iy], dim[X], VISITED_CHARS) - map[iy]
		> range[X][MAXR_MAP] - 1)
	{
		range[X][MAXR_MAP] = ft_sn_strrchr(map[iy], dim[X], VISITED_CHARS)
			- map[iy] + 1;
	}
	++range[Y][MAXR_MAP];
}

void	get_map_range(char *map[], const uint64_t dim[2], int64_t range[2][2])
{
	uint64_t	iy;

	range[X][MINR_MAP] = dim[X] - 1;
	iy = 0;
	while (iy < dim[Y])
	{
		if (!ft_sn_strchr(map[iy], dim[X], VISITED_CHARS))
		{
			if (!range[Y][MAXR_MAP])
				++range[Y][MINR_MAP];
		}
		else
			__get_map_range(map, dim, range, iy);
		++iy;
	}
	range[Y][MAXR_MAP] += range[Y][MINR_MAP] - 1;
}

uint32_t	flood_fill(t_pars *pars, char *map[], uint64_t dim[2])
{
	if (recursive_shi(map, dim, pars->player[X], pars->player[Y]))
		return (pars->error = UNCLOSED_MAP);
	get_map_range(map, dim, pars->range_map);
	if (make_new_map(pars, map, pars->range_map, pars->doors))
		return (pars->error);
	return (pars->error);
}
