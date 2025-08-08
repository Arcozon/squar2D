/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:23:35 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/08 20:34:22 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static const char	*g_pars_errors_begin[] = {"None\n",
	"Wrong arguments\n\tUsage: ", "Wrong file extension: `",
	"Can't open map: `", "Wrong key: '", "Missing color: ",
	"Color is redefined: `", "Wrong format color: `", "Missing texture: ",
	"Texture is redefined: ", "Can't open texture: `", "Missing map\n",
	"No players\n", "Too many players: ", "Map is not closed\n",
	"Unknown char in map: `"};

static const char	*g_pars_errors_end[] = {0, " <FILE"DOT_CUB">\n",
	"' must end with "DOT_CUB"\n", "'\n", "'\n", "\n", "'\n", "'\n", "\n", "'\n",
	"'\n", 0, 0, " players in the map\n", 0, "'\n"};

static const char	*g_cub_errors_begin[] = {"None\n", "Malloc error\n",
	"Read error\n", "Mlx init error\n", "Window init error\n",
	"Image creation error\n"};

static const char	*g_cub_errors_end[] = {0, 0, 0, 0, 0, 0};

uint32_t	perror_pars(uint32_t err, char context[])
{
	const char		*beg_err = g_pars_errors_begin[err];
	const char		*end_err = g_pars_errors_end[err];
	const uint64_t	len_err = ft_strlen(beg_err);

	write(2, beg_err, len_err);
	if (end_err)
	{
		write(2, context, ft_strlen(context));
		write(2, end_err, ft_strlen(end_err));
	}
	return (err);
}

uint32_t	perror_cub(t_cub cub)
{
	if (!(cub.pars.error || cub.pars.pmlx.error || cub.error))
		return (NO_ERR);
	write(2, "Error\n", 6);
	write(2, cub.pname, ft_strlen(cub.pname));
	write(2, ": ", 2);
	if (cub.pars.error)
		return (perror_pars(cub.pars.error, cub.pars.err_context));
	if (cub.pars.pmlx.error)
	{
		cub.error = cub.pars.pmlx.error;
		ft_strlcpy(cub.err_context, cub.pars.pmlx.err_context,
			sizeof(cub.err_context));
	}
	write(2, g_cub_errors_begin[cub.error],
		ft_strlen(g_cub_errors_begin[cub.error]));
	if (g_cub_errors_end[cub.error])
	{
		write(2, cub.err_context, ft_strlen(cub.err_context));
		write(2, g_cub_errors_end[cub.error],
			ft_strlen(g_cub_errors_end[cub.error]));
	}
	return (cub.error);
}
