/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:14:00 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/13 15:40:09 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	skip_spaces(char *line[])
{
	if (!*line)
		return ;
	while (*line[0] == ' ')
		++*line;
}

void	skip_key_space(char *line[])
{
	if (!*line)
		return ;
	while (*line[0] && *line[0] != ' ')
		++*line;
	while (*line[0] == ' ')
		++*line;
}

int	ft_str_space_cmp(const char *str, const char *pat)
{
	uint32_t	i;

	i = 0;
	while (pat[i] && str[i] == pat[i])
		++i;
	return (!pat[i] && str[i] == ' ');
}

__attribute__((pure))
int	is_color(const char *line)
{
	return (ft_str_space_cmp(line, KEY_CEILING) || ft_str_space_cmp(line, KEY_FLOOR));
}

__attribute__((pure))
int	is_texture(const char *line)
{
	return (ft_str_space_cmp(line, KEY_NORTH)
		|| ft_str_space_cmp(line, KEY_EAST)
		|| ft_str_space_cmp(line, KEY_SOUTH)
		|| ft_str_space_cmp(line, KEY_WEST));
}

int	ft_isdigit(const char c)
{
	return (c >= '0' && c <= '9');
}

int	is_map(const char *line)
{
	uint32_t	i;
	uint32_t	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (ft_strchr(MAP_CHARS, line[i]))
			++count;
		++i;
	}
	return (count > i * 3 / 4);
}
