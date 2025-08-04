/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:25:43 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/04 13:47:15 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_mlx(t_mlx *mlx)
{
	if (mlx->win_img)
		mlx_destroy_image(mlx->mlx_ptr, mlx->win_img);
	if (mlx->win_ptr)
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	if (mlx->mlx_ptr)
	{
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
	}
}

void	free_pars(t_pars *pars)
{
	if (pars->ea_texture.imgptr)
		mlx_destroy_image(pars->pmlx.mlx_ptr, pars->ea_texture.imgptr);
	if (pars->we_texture.imgptr)
		mlx_destroy_image(pars->pmlx.mlx_ptr, pars->we_texture.imgptr);
	if (pars->no_texture.imgptr)
		mlx_destroy_image(pars->pmlx.mlx_ptr, pars->no_texture.imgptr);
	if (pars->so_texture.imgptr)
		mlx_destroy_image(pars->pmlx.mlx_ptr, pars->so_texture.imgptr);
	free(pars->rd.line);
	pars->rd.line = 0;
	if (pars->rd.fd >= 0)
	{
		close (pars->rd.fd);
		pars->rd.fd = -1;
	}
	free_mlx(&pars->pmlx);
}

void	free_cub(t_cub *cub)
{
	free_pars(&cub->pars);
}
