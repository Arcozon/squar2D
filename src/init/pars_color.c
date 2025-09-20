/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:17:42 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/20 12:14:20 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

__attribute__((always_inline))
static inline uint32_t	get_col(char **line, t_clr *color)
{
	uint32_t	nb;
	uint32_t	i;

	i = 0;
	nb = 0;
	while (ft_isdigit((*line)[i]))
	{
		nb = nb * 10 + (*line)[i] - '0';
		if (nb > 255)
			return (WRONG_FORMAT_COLOR);
		++i;
	}
	*line += i;
	if (i == 0)
		return (WRONG_FORMAT_COLOR);
	color->rgb = (color->rgb << __CHAR_BIT__) + nb;
	return (NO_ERR);
}

__attribute__((always_inline, flatten))
static inline uint32_t	read_color(char *line, t_pars *pars, t_clr *col)
{
	skip_key_space(&line);
	ft_strlcpy(pars->err_context, line, sizeof(pars->err_context));
	if (get_col(&line, col) || *line != ',')
		return (pars->error = WRONG_FORMAT_COLOR);
	++line;
	if (get_col(&line, col) || *line != ',')
		return (pars->error = WRONG_FORMAT_COLOR);
	++line;
	if (get_col(&line, col) || *line != '\0')
		return (pars->error = WRONG_FORMAT_COLOR);
	pars->err_context[0] = '\0';
	return (NO_ERR);
}

uint32_t	pars_color(t_pars *pars, char *line)
{
	if (line[0] == 'C')
	{
		if (pars->ceiling_defined)
		{
			ft_strlcpy(pars->err_context, "Ceiling", sizeof(pars->err_context));
			return (pars->error = REDEFINED_COLOR);
		}
		pars->ceiling_defined = 1;
		return (read_color(line, pars, &pars->color_ceiling));
	}
	if (line[0] == 'F')
	{
		if (pars->floor_defined)
		{
			ft_strlcpy(pars->err_context, "Floor", sizeof(pars->err_context));
			return (pars->error = REDEFINED_COLOR);
		}
		pars->floor_defined = 1;
		return (read_color(line, pars, &pars->color_floor));
	}
	return (NO_ERR);
}

uint32_t	pars_color_bns(t_pars *pars, char *line)
{
	const char	*keys[] = {KEY_MM_PLAYER, KEY_MM_VIEW, KEY_MM_WALL,
		KEY_MM_EMPTY, KEY_MM_D_OPEN, KEY_MM_D_CLOSE, 0};
	t_clr		**p_clr;
	uint32_t	i;

	if (is_color(line))
		return (pars_color(pars, line));
	p_clr = (t_clr *[]){&pars->mmap_player, &pars->mmap_view,
		&pars->mmap_wall, &pars->mmap_empty,
		&pars->mmap_d_open, &pars->mmap_d_closed};
	i = 0;
	while (keys[i])
	{
		if (ft_str_space_cmp(line, keys[i]))
			return (read_color(line, pars, p_clr[i]));
		++i;
	}
	return (pars->error);
}
