/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:01:11 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/30 15:01:57 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	check_easy_errors(t_pars *pars, int ac, char *av[])
{
	if (ac != 2)
	{
		ft_strlcpy(pars->err_context, av[0], sizeof(pars->err_context));
		return (pars->error = ERR_ARGS);
	}
	ft_strlcpy(pars->err_context, av[1], sizeof(pars->err_context));
	if (!ft_strendcmp(av[1], DOT_CUB))
	{
		if (!ft_strendcmp(av[1], DOT_CUBNS))
			return (pars->error = NOT_DOT_CUB);
		pars->bonus = 1;
	}
	pars->rd.fd = open(av[1], O_RDONLY);
	if (pars->rd.fd < 0)
		return (pars->error = CANT_OPN_MAP);
	pars->err_context[0] = '\0';
	return (NO_ERR);
}

char	*get_pname(char av0[])
{
	uint64_t	slash_av0;

	slash_av0 = ft_strlen(av0);
	while (slash_av0-- && av0[slash_av0] != '/')
		;
	return (av0 + slash_av0 + 1);
}

void	init_pars(t_pars *pars)
{
	pars->rd.fd = -1;
	pars->fov = BASE_FOV;
	pars->p_speed = BASE_PLAYER_SPEED;
	pars->angle_speed = BASE_VANGLE_DELTA;
	pars->sensitivity = BASE_SENSITIVITY;
	pars->delta_angle = 0.f;
	pars->mmap_player.rgb = MMAP_CLR_PLAYR;
	pars->mmap_wall.rgb = MMAP_CLR_WALL;
	pars->mmap_view.rgb = MMAP_CLR_VIEW;
	pars->mmap_empty.rgb = MMAP_CLR_MTY;
	pars->mmap_d_open.rgb = MMAP_CLR_D_OPEN;
}

uint32_t	init_cub(t_cub *cub, int ac, char *av[])
{
	static char	default_pname[] = "Cub3d";

	ft_bzero(cub, sizeof(*cub));
	if (!av[0])
		av[0] = default_pname;
	cub->pname = get_pname(av[0]);
	init_pars(&cub->pars);
	if (check_easy_errors(&cub->pars, ac, av))
		return (cub->pars.error);
	cub->bonus = cub->pars.bonus;
	if (cub_init_mlx(&cub->pars.pmlx, cub->pname, av[1], cub))
		return (cub->pars.pmlx.error);
	if (parsing(&cub->pars))
		return (cub->pars.error);
	fill_game(&cub->pars, &cub->game);
	return (cub->error);
}
