/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:25:43 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/25 19:51:19 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_vector(t_vector *vector)
{
	free(vector->u_ptr.void_ptr);
	vector->u_ptr.void_ptr = 0;
}

void	free_2d_vector(t_vector *vector)
{
	uint64_t	i;

	if (!vector->u_ptr.void_ptr)
		return ;
	i = 0;
	while (i < vector->size)
	{
		free_vector(&vector->u_ptr.vect_ptr[i]);
		++i;
	}
	free_vector(vector);
}

void	free_strstr(char **strstr)
{
	uint32_t	i;

	i = 0;
	if (strstr)
	{
		while (strstr[i])
		{
			free(strstr[i]);
			++i;
		}
		free(strstr);
	}
}

void	free_mlx(t_mlx *mlx)
{
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
	free(pars->rd.line);
	pars->rd.line = 0;
	if (pars->rd.fd >= 0)
	{
		close (pars->rd.fd);
		pars->rd.fd = -1;
	}
	free_strstr(pars->resized_map);
	free(pars->map);
	free_2d_vector(&pars->vec_map);
	free_mlx(&pars->pmlx);
}

void	free_cub(t_cub *cub)
{
	free_pars(&cub->pars);
}
