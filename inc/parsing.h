/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:21:56 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/17 16:10:03 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "types.h"
# include "s_vector.h"

struct s_read
{
	int			fd;
	int			br;
	char		content[BUFF_SIZE];

	char		*line;
	uint8_t		flags;
	uint32_t	error;
};

char		*gnl(t_read *rd);
void		skip_spaces(char *line[]);
void		skip_key_space(char **line);
int			ft_str_space_cmp(const char *str, const char *pat);
int			is_color(char *line);
int			is_texture(char *line);
int			ft_isdigit(char c);
int			is_map(char *line);

uint32_t	pars_color(t_pars *pars, char *line);
uint32_t	pars_texture(t_pars *pars, char *line);
uint32_t	pars_data(t_pars *pars);
uint32_t	pars_map(t_pars *pars);

uint32_t	flood_fill(t_pars *pars, char **map, uint64_t dim[2]);
uint32_t	parsing(t_pars *pars);

#endif
