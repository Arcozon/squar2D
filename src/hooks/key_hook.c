/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:40:04 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/08 16:52:21 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press_hook(int key, t_cub *cub)
{
	if (key == XK_Escape)
		mlx_loop_end(cub->pars.pmlx.mlx_ptr);
	(void)key, (void)cub;
	return (0);
}

int		key_release_hook(int key, t_cub *cub)
{
	if (key == XK_Escape)
		mlx_loop_end(cub->pars.pmlx.mlx_ptr);
	(void)key, (void)cub;
	return (0);
}
