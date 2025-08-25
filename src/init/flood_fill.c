/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 16:09:13 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/25 20:10:52 by gaeudes          ###   ########.fr       */
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

// void	set_back_to_space(char **map, uint64_t dim[2])
// {
// 	uint64_t	i;
// 	uint64_t	j;

// 	i = 0;
// 	while (i < dim[Y])
// 	{
// 		j = 0;
// 		while (j < dim[X])
// 		{
// 			if (map[i][j] == VISITED_CHAR)
// 				map[i][j] = MTY_CHAR;
// 			++j;
// 		}
// 		++i;
// 	}
// }

void	get_map_range(char *map[], const uint64_t dim[2], int64_t range[2][2])
{
	uint64_t	iy;

	range[X][MINR_MAP] = dim[X] - 1;
	iy = 0;
	while (iy < dim[Y])
	{
		if (!ft_strchr(map[iy], VISITED_CHAR))
		{
			if (!range[Y][MAXR_MAP])
				++range[Y][MINR_MAP];
		}
		else
		{
			if (ft_strchr(map[iy], VISITED_CHAR) - map[iy] < range[X][MINR_MAP])
				range[X][MINR_MAP] = ft_strchr(map[iy], VISITED_CHAR) - map[iy];
			if (ft_strrchr(map[iy], VISITED_CHAR) - map[iy]
				> range[X][MAXR_MAP] - 1)
				range[X][MAXR_MAP] = ft_strrchr(map[iy], VISITED_CHAR)
					- map[iy] + 1;
			++range[Y][MAXR_MAP];
		}	
		++iy;
	}
	range[Y][MAXR_MAP] += range[Y][MINR_MAP] - 1;
}

char	*ft_dupmapline(const char *old_line, const uint64_t start,
	const uint64_t len)
{
	uint64_t	i;
	char		*new_line;

	new_line = malloc(sizeof(*new_line) * len);
	if (!new_line)
		return (0);
	ft_memcpy(new_line, old_line + start, len);
	i = 0;
	while (i < len)
	{
		if (new_line[i] == MTY_CHAR)
			new_line[i] = WALL_CHAR;
		else if (new_line[i] == VISITED_CHAR)
			new_line[i] = MTY_CHAR;
		++i;
	}
	return (new_line);
}

uint64_t	make_new_map(t_pars *pars, char *old_map[], int64_t	range[2][2])
{
	const uint64_t	ndim[2] = {(range[X][MAXR_MAP] - range[X][MINR_MAP] + 2),
		(range[Y][MAXR_MAP] - range[Y][MINR_MAP] + 3)};
	uint64_t		iy;
	char			**new_map;

	new_map = ft_calloc(sizeof(*new_map) * ndim[Y]);
	if (!new_map)
		return (pars->syscall_error = E_MLC);
	iy = 0;
	while (iy < ndim[Y])
	{
		new_map[iy] = ft_dupmapline(old_map[range[Y][MINR_MAP] - 1 + iy],
				range[X][MINR_MAP] - 1, ndim[X]);
		if (!new_map[iy])
			return (pars->syscall_error = E_MLC);
		++iy;
	}
	pars->resized_map = new_map;
	pars->player[X] -= range[X][MINR_MAP] - 1;
	pars->player[Y] -= range[Y][MINR_MAP] - 1;
	pars->dim[X] = ndim[X];
	pars->dim[Y] = ndim[Y];
	return (NO_ERR);
}

uint32_t	flood_fill(t_pars *pars, char *map[], uint64_t dim[2])
{
	if (recursive_shi(map, dim, pars->player[X], pars->player[Y]))
		return ((pars->error = UNCLOSED_MAP) || pars->syscall_error);
	get_map_range(map, dim, pars->range_map);
	if (make_new_map(pars, map, pars->range_map))
		return (pars->error || pars->syscall_error);
	return (pars->error || pars->syscall_error);
}
