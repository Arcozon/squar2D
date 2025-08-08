/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:21:56 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/08 12:24:51 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "types.h"

struct s_read
{
	int			fd;
	int			br;
	char		content[BUFF_SIZE];

	char		*line;
	uint8_t		flags;
	uint32_t	error;
};

# define VECTOR_BASE_SIZE 16

struct s_vector
{
	uint8_t		sizeof_type;
	union
	{
		void		*void_ptr;
		char		*char_ptr;
		char		**cchar_ptr;
		t_vector	*vect_ptr;
	}	u_ptr;

	uint64_t	size;
	uint64_t	capacity;
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

uint32_t	parsing(t_pars *pars);

#endif
