/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:40:04 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/08 19:44:37 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press_hook(int key, t_cub *cub)
{
	if (key == XK_Escape)
		mlx_loop_end(cub->pars.pmlx.mlx_ptr);
	else if (key == XK_space)
	{
		t_vector vmap = cub->pars.vec_map;
		for (uint64_t i = 0; i < vmap.size; ++i)
		{
			printf("%.*s\n", (int)vmap.u_ptr.vect_ptr[i].size,  vmap.u_ptr.vect_ptr[i].u_ptr.char_ptr);
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
