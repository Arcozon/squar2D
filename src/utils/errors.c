/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:23:35 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/23 13:39:32 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static const char	*g_errors_begin[ERR_PARS_MAX] = {"None\n",
	"Malloc error\n", "Read error\n", "Mlx init error\n",
	"Window init error\n", "Image creation error\n",
	"Wrong arguments\n\tUsage: ", "Wrong file extension: `",
	"Can't open map: `", "Wrong key: '", "Missing color: ",
	"Color is redefined: `", "Wrong format color: `", "Missing texture: ",
	"Texture is redefined: ", "Can't open texture: `", "Missing map\n",
	"No players\n", "Too many players: ", "Map is not closed\n",
	"Unknown char in map: `", "The door in ", "The door in ",
	"Wrong format float: `"};

static const char	*g_errors_end[ERR_PARS_MAX] = {0, 0, 0, 0, 0, 0,
	" <FILE>"DOT_CUB"[ns]\n", "' must end with "DOT_CUB" or "DOT_CUBNS"\n",
	"'\n", "'\n", "\n", "'\n", "'\n", "\n", "'\n", "'\n", 0, 0,
	" players in the map\n", 0, "'\n",
	" does not have 2 empty box on opposite sides\n",
	" is next to another door\n", "'\n"};

uint32_t	perror_cub(t_cub cub)
{
	if (!(cub.pars.error || cub.pars.pmlx.error || cub.error))
		return (NO_ERR);
	write(2, "Error\n", 6);
	write(2, cub.pname, ft_strlen(cub.pname));
	write(2, ": ", 2);
	if (cub.pars.error)
	{
		cub.error = cub.pars.error;
		ft_strlcpy(cub.err_context, cub.pars.err_context,
			sizeof(cub.err_context));
	}
	else if (cub.pars.pmlx.error)
	{
		cub.error = cub.pars.pmlx.error;
		ft_strlcpy(cub.err_context, cub.pars.pmlx.err_context,
			sizeof(cub.err_context));
	}
	write(2, g_errors_begin[cub.error], ft_strlen(g_errors_begin[cub.error]));
	if (g_errors_end[cub.error])
	{
		write(2, cub.err_context, ft_strlen(cub.err_context));
		write(2, g_errors_end[cub.error],
			ft_strlen(g_errors_end[cub.error]));
	}
	return (cub.error);
}
