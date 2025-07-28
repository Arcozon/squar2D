/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:23:35 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/28 16:45:05 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static const char	*g_pars_errors_begin[] = {"None\n", "Wrong arguments\n\tUsage: ",
	"Wrong file extension: ", "Can't open map: ", "Wrong format",
	"Missing color: ", "Color is redefined: ", "Wrong format color:",
	"Missing texture: ", "Texture is redefined: ", "Can't open texture: ",
	"Too many players", "Map is not closed", "Unknown char in map: "};

static const char	*g_pars_errors_end[] = {""}

uint32_t	perror_pars(uint32_t err, char context[], char *pname)
{
	const char		*str_err = pars_errors_begin[err];
	const uint64_t	len_err = ft_strlen(str_err);
	const char		need_context[] = "01110111111001";

	write(2, str_err, len_err);
	
	return (err);
}

uint32_t	perror_cub(t_cub cub)
{
	if (cub.pars.error || cub.pars.pmlx.error || cub.error)
	{
		write(2, "Error\n", 6);
		write(2, cub.pname, ft_strlen(cub.pname));
		write(2, ": ", 2);
	}
	if (cub.pars.error)
		return (perror_pars(cub.pars.error, cub.pars.err_context, cub.pname));
	if (cub.pars.pmlx.error)
		return (perror_mlx(cub.pars.pmlx, cub.pname));
}
