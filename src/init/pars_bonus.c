/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 11:48:22 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/13 17:41:14 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

__attribute__((pure))
int	is_color_bns(const char *line)
{
	return (is_color(line)
		|| ft_str_space_cmp(line, KEY_MM_PLAYER)
		|| ft_str_space_cmp(line, KEY_MM_VIEW)
		|| ft_str_space_cmp(line, KEY_MM_WALL)
		|| ft_str_space_cmp(line, KEY_MM_EMPTY)
		|| ft_str_space_cmp(line, KEY_MM_D_OPEN)
		|| ft_str_space_cmp(line, KEY_MM_D_CLOSE));
}

__attribute__((pure))
int	is_texture_bns(const char *line)
{
	return (is_texture(line)
		|| ft_str_space_cmp(line, KEY_DOOR));
}

int	is_map_bns(const char *line)
{
	uint32_t	i;
	uint32_t	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (ft_strchr(MAP_CHARS""MAP_CHARS_BNS, line[i]))
			++count;
		++i;
	}
	return (count > i * 3 / 4);
}



uint32_t	pars_map_bonus(t_pars *pars)
{
	return (pars->error);
}

uint32_t	pars_data_bonus(t_pars *pars)
{
	char	*line;

	while (!(pars->rd.flags & R_DONE) && !pars->error)
	{
		line = gnl(&pars->rd);
		skip_spaces(&line);
		if (!line || !line[0])
			continue ;
		if (is_color_bns(line))
			pars_color_bns(pars, line);
		else if (is_texture_bns(line))
			pars_texture_bonus(pars, line);
		else if (is_map_bns(line))
			break ;
		else
		{
			ft_strnlcpy(pars->err_context, line,
				sizeof(pars->err_context), index_strchr(line, ' '));
			return (pars->error = WRONG_KEY);
		}
	}
	DEBUG(KEY_MM_PLAYER": %x %x %x", pars->mmap_player.s_mask.r, pars->mmap_player.s_mask.g, pars->mmap_player.s_mask.b)
	DEBUG(KEY_MM_WALL": %x %x %x", pars->mmap_wall.s_mask.r, pars->mmap_wall.s_mask.g, pars->mmap_wall.s_mask.b)
	DEBUG(KEY_MM_EMPTY": %x %x %x", pars->mmap_empty.s_mask.r, pars->mmap_empty.s_mask.g, pars->mmap_empty.s_mask.b)
	DEBUG(KEY_MM_VIEW": %x %x %x", pars->mmap_view.s_mask.r, pars->mmap_view.s_mask.g, pars->mmap_view.s_mask.b)
	DEBUG(KEY_MM_D_OPEN": %x %x %x", pars->mmap_d_open.s_mask.r, pars->mmap_d_open.s_mask.g, pars->mmap_d_open.s_mask.b)
	DEBUG(KEY_MM_D_CLOSE": %x %x %x", pars->mmap_d_closed.s_mask.r, pars->mmap_d_closed.s_mask.g, pars->mmap_d_closed.s_mask.b)
	if (pars->rd.error)
		pars->error = pars->rd.error;
	return (is_data_full(pars));
}
