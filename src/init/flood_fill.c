/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 16:09:13 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/25 19:19:36 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define VISITED_CHAR 'f'

uint32_t	recursive_shi(char **map,
	const uint64_t dim[2], uint64_t x, uint64_t y)
{
	if (x < 0 || x >= dim[X] || y < 0 || y >= dim[Y])
		return (UNCLOSED_MAP);
	if (map[y][x] == VISITED_CHAR || map[y][x] == WALL_CHAR)
		return (0);
	map[y][x] = VISITED_CHAR;
	if (recursive_shi(map, dim, x - 1, y)
		|| recursive_shi(map, dim, x, y - 1)
		|| recursive_shi(map, dim, x + 1, y)
		|| recursive_shi(map, dim, x, y + 1))
		return (UNCLOSED_MAP);
	return (0);
}

void	set_back_to_space(char **map, uint64_t dim[2])
{
	uint64_t	i;
	uint64_t	j;

	i = 0;
	while (i < dim[Y])
	{
		j = 0;
		while (j < dim[X])
		{
			if (map[i][j] == VISITED_CHAR)
				map[i][j] = ' ';
			++j;
		}
		++i;
	}
}
enum {MIN_MAP, MAX_MAP};
void	resize_map(char *map[], const uint64_t dim[2])
{
	int64_t	range[2][2];
	uint64_t	iy;

	range[X][MIN_MAP] = dim[X] - 1;
	range[X][MAX_MAP] = 0;
	range[Y][MIN_MAP] = 0;
	range[Y][MAX_MAP] = 0;
	iy = 0;
	while (iy < dim[Y])
	{
		if (!ft_strchr(map[iy], VISITED_CHAR))
		{
			if (!range[Y][MAX_MAP])
				++range[Y][MIN_MAP];
		}
		else
		{
			if (ft_strchr(map[iy], VISITED_CHAR) - map[iy] < range[X][MIN_MAP])
				range[X][MIN_MAP] = ft_strchr(map[iy], VISITED_CHAR) - map[iy];
			if (ft_strrchr(map[iy], VISITED_CHAR) - map[iy] > range[X][MAX_MAP])
				range[X][MAX_MAP] = ft_strrchr(map[iy], VISITED_CHAR) - map[iy] + 1;
			DEBUG("[%s]", ft_strrchr(map[iy], VISITED_CHAR))
			++range[Y][MAX_MAP];
		}	
		++iy;
	}
	DEBUG("%ld|%ld -- %ld|%ld", range[X][MIN_MAP], range[X][MAX_MAP], range[Y][MIN_MAP], range[Y][MAX_MAP])
}

uint32_t	flood_fill(t_pars *pars, char **map, uint64_t dim[2])
{
	if (recursive_shi(map, dim, pars->player[X], pars->player[Y]))
		return ((pars->error = UNCLOSED_MAP) || pars->syscall_error);
	resize_map(map, dim);
	set_back_to_space(map, dim);
	return (pars->error || pars->syscall_error);
}
