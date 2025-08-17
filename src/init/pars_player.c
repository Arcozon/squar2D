/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 16:50:23 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/17 16:55:41 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

uint32_t	count_players(t_pars *pars, char **map, uint64_t dim[2])
{
	uint64_t	count;
	uint64_t	i;
	uint64_t	j;

	count = 0;
	i = 0;
	while (i < dim[Y])
	{
		j = -1;
		while (++j < dim[X])
			if (ft_strchr(PLAYER_CHARS, map[i][j]))
				++count;
		++i;
	}
	if (count == 0)
		return (pars->error = MISSING_PLAYER);
	else if (count > 1)
	{
		ft_lutoacpy(count, pars->err_context, sizeof(pars->err_context));
		return (pars->error = TOO_MANY_PLAYER);
	}
	find_player(map, dim, pars->player);
	set_angle_player(&pars->view_angle, map, pars->player);
	return (NO_ERR);
}
