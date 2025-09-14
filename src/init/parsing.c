/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 17:59:44 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/14 16:51:59 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	is_data_full(t_pars *pars)
{
	if (pars->error)
		return (pars->error);
	if (!pars->ceiling_defined || !pars->floor_defined)
	{
		ft_strlcpy(pars->err_context, "Ceiling", sizeof(pars->err_context));
		if (!pars->floor_defined)
			ft_strlcpy(pars->err_context, "Floor", sizeof(pars->err_context));
		return (pars->error = MISSING_COLOR);
	}
	if (!pars->ea_texture.p_img)
		ft_strlcpy(pars->err_context, "East", sizeof(pars->err_context));
	else if (!pars->we_texture.p_img)
		ft_strlcpy(pars->err_context, "West", sizeof(pars->err_context));
	else if (!pars->no_texture.p_img)
		ft_strlcpy(pars->err_context, "North", sizeof(pars->err_context));
	else if (!pars->so_texture.p_img)
		ft_strlcpy(pars->err_context, "South", sizeof(pars->err_context));
	else
		return (NO_ERR);
	return (pars->error = MISSING_TEXTURE);
}

uint32_t	pars_data(t_pars *pars)
{
	char	*line;

	while (!(pars->rd.flags & R_DONE) && !pars->error)
	{
		line = gnl(&pars->rd);
		skip_spaces(&line);
		if (!line || !line[0])
			continue ;
		if (is_color(line))
			pars_color(pars, line);
		else if (is_texture(line))
			pars_texture(pars, line);
		else if (is_map(line))
			break ;
		else
		{
			ft_strnlcpy(pars->err_context, line,
				sizeof(pars->err_context), index_strchr(line, ' '));
			return (pars->error = WRONG_KEY);
		}
	}
	if (pars->rd.error)
		pars->error = pars->rd.error;
	return (is_data_full(pars));
}

uint32_t	parsing(t_pars *pars)
{
	pars->rd.flags = R_CUT_E_SPC;
	if (!pars->bonus)
	{
		if (pars_data(pars) || pars_map(pars))
			return (pars->error);
	}
	else
	{
		if (pars_data_bonus(pars) || pars_map_bonus(pars))
			return (pars->error);
	}
	return (pars->error);
}
