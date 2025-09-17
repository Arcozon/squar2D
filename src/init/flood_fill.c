/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 16:09:13 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/17 15:49:08 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define VISITED_EMPTY	'f'
#define VISITED_DOOR	'd'
#define VISITED_CHARS	"fd"

__attribute__((hot))
uint32_t	recursive_shi(char **map,
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

void	get_map_range(char *map[], const uint64_t dim[2], int64_t range[2][2])
{
	uint64_t	iy;

	range[X][MINR_MAP] = dim[X] - 1;
	iy = 0;
	while (iy < dim[Y])
	{
		if (!ft_s_strchr(map[iy], VISITED_CHARS))
		{
			if (!range[Y][MAXR_MAP])
				++range[Y][MINR_MAP];
		}
		else
		{
			if (ft_s_strchr(map[iy], VISITED_CHARS) - map[iy] < range[X][MINR_MAP])
				range[X][MINR_MAP] = ft_s_strchr(map[iy], VISITED_CHARS) - map[iy];
			if (ft_s_strrchr(map[iy], VISITED_CHARS) - map[iy]
				> range[X][MAXR_MAP] - 1)
				range[X][MAXR_MAP] = ft_s_strrchr(map[iy], VISITED_CHARS)
					- map[iy] + 1;
			++range[Y][MAXR_MAP];
		}	
		++iy;
	}
	range[Y][MAXR_MAP] += range[Y][MINR_MAP] - 1;
}

char	*ft_dupmapline(const char *old_line, const uint64_t info[2],
	t_doors	doors, const uint32_t n_newline)
{
	uint64_t	i;
	char		*new_line;

	new_line = malloc(sizeof(*new_line) * info[0]);
	if (!new_line)
		return (NULL);
	ft_memcpy(new_line, old_line + info[1] , info[0]);
	i = 0;
	while (i < info[0])
	{
		if (new_line[i] == MTY_CHAR)
			new_line[i] = WALL_CHAR;
		else if (ft_strchr(VISITED_CHARS, new_line[i]))
		{
			if (new_line[i] == VISITED_DOOR)
				DEBUG("DOOR")
			if (new_line[i] == VISITED_DOOR && add_door(doors, i, n_newline) == E_MLX)
				return (free(new_line), NULL);
			new_line[i] = MTY_CHAR;
		}
		++i;
	}
	return (new_line);
}

uint64_t	make_new_map(t_pars *pars, char *old_map[], int64_t	range[2][2], t_doors doors)
{
	const uint64_t	ndim[2] = {(range[X][MAXR_MAP] - range[X][MINR_MAP] + 2),
		(range[Y][MAXR_MAP] - range[Y][MINR_MAP] + 3)};
	uint64_t		iy;
	char			**new_map;

	new_map = ft_calloc(sizeof(*new_map) * ndim[Y]);
	if (!new_map)
		return (pars->error = E_MLC);
	iy = 0;
	while (iy < ndim[Y])
	{
		new_map[iy] = ft_dupmapline(old_map[range[Y][MINR_MAP] - 1 + iy],
				(uint64_t []){ndim[X], range[X][MINR_MAP] - 1}, doors, iy);
		if (!new_map[iy])			
			return (free_strstr(new_map, iy),  pars->error = E_MLC);
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
		return (pars->error = UNCLOSED_MAP);
	get_map_range(map, dim, pars->range_map);
	if (make_new_map(pars, map, pars->range_map, pars->doors))
		return (pars->error);
	return (pars->error);
}
