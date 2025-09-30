/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:30:53 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/30 13:31:09 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_title(char title[BUFF_SIZE], const char pname[],
	const char map_name[])
{
	if (ft_strendcmp(map_name, DOT_CUBNS))
		ft_strlcat(title, "[Bonus] ", BUFF_SIZE);
	ft_strlcat(title, pname, BUFF_SIZE);
	if (title[0] >= 'a' && title[0] <= 'z')
		title[0] -= 'a' - 'A';
	ft_strlcat(title, ": ", BUFF_SIZE);
	ft_strlcat(title, map_name, BUFF_SIZE);
	if (ft_strendcmp(title, DOT_CUB))
		title[ft_strlen(title) - ft_strlen(DOT_CUB)] = '\0';
	else if (ft_strendcmp(title, DOT_CUBNS))
		title[ft_strlen(title) - ft_strlen(DOT_CUBNS)] = '\0';
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
