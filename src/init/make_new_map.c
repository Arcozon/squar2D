/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_new_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:44:23 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/30 13:47:00 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_dupmapline(const char *old_line, const uint64_t info[2],
	t_doors	doors, const uint32_t n_newline)
{
	uint64_t	i;
	char		*new_line;

	new_line = malloc(sizeof(*new_line) * info[0]);
	if (!new_line)
		return (NULL);
	ft_memcpy(new_line, old_line + info[1], info[0]);
	i = 0;
	while (i < info[0])
	{
		if (new_line[i] == MTY_CHAR)
			new_line[i] = WALL_CHAR;
		else if (ft_strchr(VISITED_CHARS, new_line[i]))
		{
			if (new_line[i] == VISITED_DOOR
				&& add_door(doors, i, n_newline) == E_MLX)
				return (free(new_line), NULL);
			new_line[i] = MTY_CHAR;
		}
		++i;
	}
	return (new_line);
}

uint64_t	make_new_map(t_pars *pars, char *old_map[],
	int64_t	range[2][2], t_doors doors)
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
			return (free_strstr(new_map, iy), pars->error = E_MLC);
		++iy;
	}
	pars->resized_map = new_map;
	pars->player[X] -= range[X][MINR_MAP] - 1;
	pars->player[Y] -= range[Y][MINR_MAP] - 1;
	pars->dim[X] = ndim[X];
	pars->dim[Y] = ndim[Y];
	return (NO_ERR);
}
