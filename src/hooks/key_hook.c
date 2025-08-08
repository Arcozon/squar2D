/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:40:04 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/08 20:58:36 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press_hook(int key, t_cub *cub)
{
	if (key == XK_Escape)
		mlx_loop_end(cub->pars.pmlx.mlx_ptr);
	else if (key == XK_space)
	{
		for (uint64_t i = 0; i < cub->pars.dim[Y]; ++i)
		{
			printf("%.*s\n", (int)cub->pars.dim[X], cub->pars.map[i]);
		}
	}
	return (0);
	(void)key, (void)cub;
}

int		key_release_hook(int key, t_cub *cub)
{
	if (key == XK_Escape)
		mlx_loop_end(cub->pars.pmlx.mlx_ptr);
	return (0);
	(void)key, (void)cub;
}
