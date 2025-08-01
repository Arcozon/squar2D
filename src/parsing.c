/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 17:59:44 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/01 15:04:58 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_str_space_cmp(char *str, char *pat)
{
	uint32_t	i;

	i = 0;
	while (pat[i] && str[i] == pat[i])
		++i;
	return (!pat[i] && str[i] == ' ');
}

int	is_color(char *line)
{
	return (ft_str_space_cmp(line, "C") || ft_str_space_cmp(line, "F"));
}

int	is_texture(char *line)
{
	return (ft_str_space_cmp(line, "NO") || ft_str_space_cmp(line, "SO")
		|| ft_str_space_cmp(line, "EA")  || ft_str_space_cmp(line, "WE"));
}

int ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int is_map(char *line)
{
	uint32_t	i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr(MAP_CHARS, line[i]))
			return (0);
		++i;
	}
	return (1);
}

uint32_t	get_col(char **line, uint32_t *color)
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
	*color = (*color << __CHAR_BIT__) + nb;
	return (NO_ERR);
}

uint32_t	read_color(char *line, t_pars *pars, uint32_t *col)
{
	++line;
	while (*line == ' ')
		++line;
	ft_strlcpy(pars->err_context, line, sizeof(pars->err_context));
	if (get_col(&line, col) || *line != ',')
		return (pars->error = WRONG_FORMAT_COLOR);
	++line;
	if (get_col(&line, col) || *line != ',')
		return (pars->error = WRONG_FORMAT_COLOR);
	++line;
	if (get_col(&line, col) || *line != '\0')
		return (pars->error = WRONG_FORMAT_COLOR);
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

uint32_t	pars_texture(t_pars *pars, char *line)
{
	return (NO_ERR);
	(void)pars, (void)line;
}

uint32_t	pars_data(t_pars *pars)
{
	char	*line;

	while (!(pars->rd.flags & R_DONE) && !pars->error)
	{
		line = gnl(&pars->rd);
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
				sizeof(pars->err_context), char_chr(line, ' '));
			return (pars->error = WRONG_KEY);
		}
	}
	DEBUG("C:%.6X", pars->color_ceiling)
	DEBUG("F:%.6X", pars->color_floor)
	return (pars->error);
}

uint32_t	parsing(t_pars *pars)
{
	if (pars_data(pars))
	 	return (pars->error);
	return (pars->error);
}
