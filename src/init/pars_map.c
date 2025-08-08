/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:37:08 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/08 20:33:52 by gaeudes          ###   ########.fr       */
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
			ft_strnlcpy(pars->err_context, line + i, sizeof(pars->err_context), 1);
			return (pars->error = UNKNOWN_CHAR);
		}
		++i;
	}
	return (NO_ERR);
}

uint32_t	normalise_map(t_pars *pars, t_vector *v_map)
{
	uint64_t	i;
	uint64_t	max_size;

	max_size = 0;
	i = 0;
	while (i < v_map->size)
	{
		if (v_map->u_ptr.vect_ptr[i].size < max_size)
			max_size = v_map->u_ptr.vect_ptr[i].size;
		++i;
	}
	i = 0;
	while (i < v_map->size)
	{
		if (realloc_vector_minsize(&v_map->u_ptr.vect_ptr[i], max_size))
			return (pars->syscall_error = E_MLC);
		++i;
	}
	return (pars->error || pars->syscall_error);
}

uint32_t	read_map(t_pars *pars)
{
	t_vector	v_line;

	if (new_vector(&pars->vec_map, sizeof(t_vector)))
		return (pars->syscall_error = E_MLC);
	while ((pars->rd.flags & R_DONE) == 0 && !pars->syscall_error && !pars->error)
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

uint32_t	count_players(t_pars *pars, t_vector *v_map)
{
	t_vector	*v_line;
	uint64_t	count;
	uint64_t	i;
	uint64_t	j;

	count = 0;
	i = 0;
	while (i < v_map->size)
	{
		j = -1;
		v_line = &v_map->u_ptr.vect_ptr[i];
		while (++j < v_line->size)
			if (ft_strchr(PLAYER_CHARS, v_line->u_ptr.char_ptr[j]))
				++count;
		++i;
	}
	if (count == 0)
		return (pars->error = MISSING_PLAYER);
	else if (count > 1)
	{
		ft_lutoacpy(count, pars->err_context, sizeof(pars->err_context));
		return (pars->error = TOO_MANY_PLAYER);
	}
	return (NO_ERR);
}

uint32_t	pars_map(t_pars *pars)
{
	if (pars->rd.flags & R_DONE)
		return (pars->error = MISSING_MAP);
	if (read_map(pars))
		return (pars->error || pars->syscall_error);
	if (count_players(pars, &pars->vec_map))
		return (pars->error || pars->syscall_error);
	return (pars->error || pars->syscall_error);
}
