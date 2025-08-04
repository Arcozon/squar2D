/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 17:59:44 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/04 14:18:55 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	parsing(t_pars *pars)
{
	pars->rd.flags = R_CUT_E_SPC;
	if (pars_data(pars))
		return (pars->error || pars->rd.error);
	return (pars->error || pars->rd.error);
}
