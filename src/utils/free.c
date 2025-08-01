/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:25:43 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/01 16:48:19 by gaeudes          ###   ########.fr       */
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
	free_mlx(&pars->pmlx);
	free(pars->rd.line);
	pars->rd.line = 0;
	if (pars->rd.fd >= 0)
	{
		close (pars->rd.fd);
		pars->rd.fd = -1;
	}
}

void	free_cub(t_cub *cub)
{
	free_pars(&cub->pars);
}
