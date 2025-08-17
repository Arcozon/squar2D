/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:37:08 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/17 16:54:41 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static uint32_t	map_forbiden_char(const char line[], t_pars *pars)
{
	uint32_t	i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr(MAP_CHARS, line[i]))
		{
			ft_strnlcpy(pars->err_context, line + i,
				sizeof(pars->err_context), 1);
			return (pars->error = UNKNOWN_CHAR);
		}
		++i;
	}
	return (NO_ERR);
}

void	change_null_into_space(char **map, const uint64_t yl, const uint64_t xl)
{
	uint64_t	i;
	uint64_t	j;

	i = 0;
	while (i < yl)
	{
		j = 0;
		while (j < xl)
		{
			if (map[i][j] == 0 || map[i][j] == '0')
				map[i][j] = ' ';
			++j;
		}
		++i;
	}
}

uint32_t	normalise_map(t_pars *pars, t_vector *v_map)
{
	uint64_t	i;
	uint64_t	max_size;

	max_size = 0;
	i = -1;
	while (++i < v_map->size)
		if (v_map->u_ptr.vect_ptr[i].size > max_size)
			max_size = v_map->u_ptr.vect_ptr[i].size;
	i = -1;
	while (++i < v_map->size)
		if (realloc_vector_minsize(&v_map->u_ptr.vect_ptr[i], max_size))
			return (pars->syscall_error = E_MLC);
	pars->dim[X] = max_size;
	pars->dim[Y] = v_map->size;
	pars->map = malloc(sizeof(char *) * pars->dim[Y]);
	if (!pars->map)
		return (pars->syscall_error = E_MLC);
	i = -1;
	while (++i < pars->dim[Y])
		pars->map[i] = v_map->u_ptr.vect_ptr[i].u_ptr.char_ptr;
	change_null_into_space(pars->map, pars->dim[Y], pars->dim[X]);
	return (pars->error || pars->syscall_error);
}

uint32_t	read_map(t_pars *pars)
{
	t_vector	v_line;

	if (new_vector(&pars->vec_map, sizeof(t_vector)))
		return (pars->syscall_error = E_MLC);
	while ((pars->rd.flags & R_DONE) == 0
		&& !pars->syscall_error && !pars->error)
	{
		v_line.u_ptr.vect_ptr = NULL;
		if (map_forbiden_char(pars->rd.line, pars))
			return (pars->error = UNKNOWN_CHAR);
		if (str_to_vector(&v_line, pars->rd.line))
			return (pars->syscall_error = E_MLC);
		if (add_elems_vector(&pars->vec_map, &v_line, 1))
			return (pars->syscall_error = E_MLC);
		gnl(&pars->rd);
		if (pars->rd.error)
			pars->syscall_error = pars->rd.error;
	}
	if (normalise_map(pars, &pars->vec_map))
		return (pars->error || pars->syscall_error);
	return (pars->error || pars->syscall_error);
}

uint32_t	pars_map(t_pars *pars)
{
	if (pars->rd.flags & R_DONE)
		return (pars->error = MISSING_MAP);
	if (read_map(pars))
		return (pars->error || pars->syscall_error);
	if (count_players(pars, pars->map, pars->dim))
		return (pars->error || pars->syscall_error);
	if (flood_fill(pars, pars->map, pars->dim))
		return (pars->error || pars->syscall_error);
	return (pars->error || pars->syscall_error);
}

