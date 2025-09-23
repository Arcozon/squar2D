/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 11:48:22 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/23 13:35:19 by gaeudes          ###   ########.fr       */
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
		|| ft_str_space_cmp(line, KEY_MM_D_OPEN));
}

__attribute__((pure))
int	is_texture_bns(const char *line)
{
	return (is_texture(line)
		|| ft_str_space_cmp(line, KEY_DOOR));
}

__attribute__((pure))
int	is_setting_bns(const char *line)
{
	return (ft_str_space_cmp(line, KEY_FOV)
		|| ft_str_space_cmp(line, KEY_PLR_TETA)
		|| ft_str_space_cmp(line, KEY_SPD_PLR)
		|| ft_str_space_cmp(line, KEY_SPD_TETA)
		|| ft_str_space_cmp(line, KEY_SPD_MOUSE));
}

__attribute__((pure))
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
			pars_color_bonus(pars, line);
		else if (is_texture_bns(line))
			pars_texture_bonus(pars, line);
		else if (is_setting_bns(line))
			pars_settings_bonus(pars, line);
		else if (is_map_bns(line))
			break ;
		else
			return (ft_strnlcpy(pars->err_context, line,
				sizeof(pars->err_context), index_strchr(line, ' ')),
				pars->error = WRONG_KEY);
	}
	if (pars->rd.error)
		pars->error = pars->rd.error;
	return (is_data_full(pars));
}
