/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 17:59:44 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/30 18:26:17 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strspacecmp(char *str, char *pat)
{
	uint32_t	i;

	i = 0;
	while (pat[i] && str[i] == pat[i])
		++i;
	return (!pat[i] && str[i] == ' ');
}

inline int	is_color(char *line)
{
	return (ft_strspacecmp(line, "C") || ft_strspacecmp(line, "F"));
}

inline int	is_texture(char *line)
{
	return (ft_strspacecmp(line, "NO") || ft_strspacecmp(line, "SO")
		|| ft_strspacecmp(line, "EA")  || ft_strspacecmp(line, "WE"));
}

inline int is_map(char *line)
{
	uint32_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '0' && line[i] != '1' && line[i] != 'W'
			&& line[i] != 'E' && line[i] != 'N' && line[i] != 'S')
			return (0);
		++i;
	}
	return (1);
}

uint32_t	pars_data(t_pars *pars)
{
	char	*line;

	while (!(pars->rd.flags & R_DONE) && !pars->error)
	{
		line = gnl(&pars->rd);
		if (!line || !line[0])
			continue ;
		if (is_color(line) != -1 && pars_color(pars, line))
			return (pars->error);
		else if (is_texture(line) != -1 && pars_color(pars, line))
			return (pars->error);
		else if (is_map(line))
			break ;
		else
		{
			ft_strnlcpy(pars->err_context, line,
				sizeof(pars->err_context), char_chr(line, ' '));
			return (pars->error = WRONG_KEY);
		}
	}
}

uint32_t	parsing(t_pars *pars)
{
	
}
