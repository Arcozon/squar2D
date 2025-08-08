/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:37:08 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/08 19:46:05 by gaeudes          ###   ########.fr       */
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
	return (pars->error || pars->syscall_error);
}

uint32_t	pars_map(t_pars *pars)
{

	if (pars->rd.flags & R_DONE)
		return (pars->error = MISSING_MAP);
	if (read_map(pars))
		return (pars->error || pars->syscall_error);
	return (pars->error || pars->syscall_error);
}
