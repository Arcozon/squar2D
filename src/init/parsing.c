/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 17:59:44 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/13 11:58:07 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	parsing(t_pars *pars)
{
	pars->rd.flags = R_CUT_E_SPC;
	if (!pars->bonus)
	{
		if (pars_data(pars) || pars_map(pars))
			return (pars->error);
	}
	else
	{
		(void)pars;
	}
	return (pars->error);
}
