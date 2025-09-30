/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:25:43 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/30 12:59:32 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_mlx(t_mlx *mlx)
{
	if (mlx->img_settings)
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_settings);
	if (mlx->img_mmap)
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_mmap);
	if (mlx->win_img)
		mlx_destroy_image(mlx->mlx_ptr, mlx->win_img);
	if (mlx->win_img_paa)
		mlx_destroy_image(mlx->mlx_ptr, mlx->win_img_paa);
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
	if (pars->ea_texture.p_img)
		mlx_destroy_image(pars->pmlx.mlx_ptr, pars->ea_texture.p_img);
	if (pars->we_texture.p_img)
		mlx_destroy_image(pars->pmlx.mlx_ptr, pars->we_texture.p_img);
	if (pars->no_texture.p_img)
		mlx_destroy_image(pars->pmlx.mlx_ptr, pars->no_texture.p_img);
	if (pars->so_texture.p_img)
		mlx_destroy_image(pars->pmlx.mlx_ptr, pars->so_texture.p_img);
	if (pars->door_texture.p_img)
		mlx_destroy_image(pars->pmlx.mlx_ptr, pars->door_texture.p_img);
	free(pars->rd.line);
	pars->rd.line = 0;
	if (pars->rd.fd >= 0)
	{
		close (pars->rd.fd);
		pars->rd.fd = -1;
	}
	free_doors(pars->doors);
	free_strstr(pars->resized_map, pars->dim[Y]);
	free(pars->map);
	free_2d_vector(&pars->vec_map);
	free_mlx(&pars->pmlx);
}

void	free_doors(t_doors doors)
{
	t_one_door	next;
	t_one_door	onedoor;
	uint32_t	i;

	i = 0;
	while (i < N_HASH_DOORS)
	{
		onedoor = doors[i];
		doors[i] = 0;
		while (onedoor)
		{
			next = onedoor->next;
			free(onedoor);
			onedoor = next;
		}
		++i;
	}
}

void	free_cub(t_cub *cub)
{
	free_pars(&cub->pars);
}
