/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:01:11 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/23 12:48:19 by gaeudes          ###   ########.fr       */
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

void	set_title(char title[BUFF_SIZE], char pname[], char map_name[])
{
	uint64_t	start;

	ft_strlcpy(title, pname, BUFF_SIZE);
	start = ft_strlen(title);
	if (start < BUFF_SIZE - 1)
	{
		ft_strlcpy(title + start, ": ", BUFF_SIZE - start);
		if (title[0] >= 'a' && title[0] <= 'z')
			title[0] -= 'a' - 'A';
		start = ft_strlen(title);
		if (start < BUFF_SIZE - 1)
		{
			ft_strlcpy(title + start, map_name, BUFF_SIZE - start);
			if (ft_strendcmp(title, DOT_CUB))
				title[ft_strlen(title) - ft_strlen(DOT_CUB)] = '\0';
		}
	}
}

uint32_t	cub_init_mlx(t_mlx *mlx, char pname[], char map_name[], t_cub *cub)
{
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		return (mlx->error = E_MLX);
	set_title(mlx->title, pname, map_name);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, W_WIDTH, W_HEIGHT, mlx->title);
	if (!mlx->win_ptr)
		return (mlx->error = E_WIN);
	mlx->win_img = mlx_new_image(mlx->mlx_ptr, W_WIDTH, W_HEIGHT);
	mlx->win_img_paa = mlx_new_image(mlx->mlx_ptr, W_WIDTH, W_HEIGHT);
	mlx->img_mmap = mlx_new_image(mlx->mlx_ptr, MMAP_WIDHT, MMAP_HEIGHT);
	mlx->img_settings = mlx_new_image(mlx->mlx_ptr, MMAP_WIDHT, MMAP_HEIGHT);
	if (!mlx->win_img || !mlx->win_img_paa || !mlx->img_mmap)
		return (mlx->error = E_IMG);
	setup_hooks(mlx, cub);
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
	if (cub_init_mlx(&cub->pars.pmlx, cub->pname, av[1], cub))
		return (cub->pars.pmlx.error);
	if (parsing(&cub->pars))
		return (cub->pars.error);
	fill_game(&cub->pars, &cub->game);
	return (cub->error);
}
