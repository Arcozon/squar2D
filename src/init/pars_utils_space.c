/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils_space.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:47:11 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/30 14:47:18 by gaeudes          ###   ########.fr       */
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
