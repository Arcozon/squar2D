/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:01:11 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/28 16:46:45 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	check_easy_errors(t_pars *pars, int ac, char *av[])
{
	if (ac != 2)
	{
		ft_strlcpy(pars->err_context, av[0], sizeof(pars->err_context))
		return (pars->error == ERR_ARGS);
	}
	ft_strlcpy(pars->err_context, av[2], sizeof(pars->err_context));
	if (!ft_strendcmp(av[2], DOT_CUB))
		return (pars->error == NOT_DOT_CUB);
	pars->fd_map = open(av[2], O_RDONLY);
	if (pars->fd_map < 0)
		return (pars->error = CANT_OPN_MAP);
	pars->err_context[0] = '\0';
	return (NO_ERR);
}

void	set_title(char title[BUFF_SIZE], char pname[], char map_name[])
{
	uint64_t	start;
	uint64_t	len;

	ft_strlcpy(title, pname, BUFF_SIZE);
	start = ft_strlen(title);
	if (start < BUFF_SIZE - 1)
	{
		ft_strlcpy(title + start, ": ", BUFF_SIZE - start);
		start = ft_strlen(title);
		if (start < BUFF_SIZE - 1)
		{
			ft_strlcpy(title + start, map_name, BUFF_SIZE - start);
			if (ft_strendcmp(title, DOT_CUB))
				title[ft_strlen(title) - ft_strlen(DOT_CUB)] = '\0';
		}
	}
	DEBUG("%s", title)
}

uint32_t	cub_init_mlx(t_mlx *mlx, char pname[], char map_name[])
{
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		return (mlx->error = E_MLX);
	set_title(mlx->title, pname, map_name);
	mlx->winptr = mlx_new_window(mlx->mlx_ptr, W_LENGHT, W_LENGHT, mlx->title);
	if (!mlx->mlx_ptr)
		return (mlx->error = E_WIN);
}

char	*get_pname(char av0[])
{
	uint64_t	slash_av0;

	slash_av0 = ft_strlen(av0);
	while (slash_av0-- && av0[slash_av0] != '\'')
		;
	return (av0 + slash_av0 + 1);
}

uint32_t	init_cub(t_cub *cub, int ac, char *av[])
{
	static char	default_pname[] = "Cub3d";
	
	ft_bzero(cub, sizeof(*cub));
	if (!av[0])
		av[0] = default_pname;
	cub->pname = get_pname(av[0]);
	if (check_easy_errors(&cub->pars, ac, av))
		return (cub->pars.error);
	if (cub_init_mlx(&cub->pars.pmlx, cub->pname, av[1]))
		return (cub->pars.pmlx.error);
	return (NO_ERR);
}
