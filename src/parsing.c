/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:01:11 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/28 10:58:39 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	check_easy_errors(t_pars *pars, int ac, char *av[])
{
	if (ac != 2)
		return (pars->error == MISSING_FILE);
	if (!ft_strendcmp(av[2], DOT_CUB))
		return (pars->error == NOT_DOT_CUB);
	pars->fd_map = open(av[2], O_RDONLY);
	if (pars->fd_map < 0)
	{
		// pars->err_context
		return (pars->error = CANT_OPN);
	}
	return (NO_ERR);
}

uint32_t	init_cub(t_cub *cub, int ac, char *av[])
{
	if (check_easy_errors(&cub->pars, ac, av))	
}
