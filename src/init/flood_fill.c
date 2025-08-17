/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 16:09:13 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/17 16:43:30 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define VISITED_CHAR 'f'

void	find_player(char **map, uint64_t dim[2], uint64_t pcoord[2])
{
	uint64_t	i;
	uint64_t	j;
	
	i = 0;
	while (i < dim[Y])
	{
		j = 0;
		while (j < dim[X])
		{
			if (ft_strchr(PLAYER_CHARS, map[i][j]))
			{
				pcoord[Y] = i;
				pcoord[X] = j;
				DEBUG("[%lu|%lu]", j, i)
				return ;
			}
			++j;
		}
		++i;
	}
}

void	set_angle_player(float *angle, char **map, const uint64_t player[2])
{
	const char	pc = map[player[Y]][player[X]];

	if (pc == 'N')
		*angle = 0.f;
	else if (pc == 'W')
		*angle = -M_PI_2;
	else if (pc == 'S')
		*angle = M_PI;
	else
		*angle = M_PI_2;
}

uint32_t	recursive_shi(char **map, const uint64_t dim[2], uint64_t x, uint64_t y)
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

uint32_t	flood_fill(t_pars *pars, char **map, uint64_t dim[2])
{
	find_player(map, dim, pars->player);
	set_angle_player(&pars->view_angle, map, pars->player);
	if (recursive_shi(map, dim, pars->player[X], pars->player[Y]))
		return ((pars->error = UNCLOSED_MAP) || pars->syscall_error);
	set_back_to_space(map, dim);
	return (pars->error || pars->syscall_error);
}
