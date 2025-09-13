/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 11:48:22 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/13 12:04:24 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_color_bns(char *line)
{
	return (is_color(line))
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
			pars_texture_bns(pars, line);
		else if (is_map_bns(line))
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
	if (pars->error)
		return (pars->error);
	return (is_data_full(pars));
}
