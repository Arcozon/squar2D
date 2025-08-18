/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:40:04 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/18 15:09:17 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_map(t_game *game)
{
	for (uint64_t i = 0; i < game->dim[Y]; ++i)
		printf("%.*s\n", (int)game->dim[X], game->map[i]);
	printf("[%f|%f] [%f]\n", (float)game->p_coo[X], (float)game->p_coo[Y], game->p_angle);
}

int	key_press_hook(int key, t_game *game)
{
	if (key == XK_Escape)
		mlx_loop_end(game->render.pmlx);
	else if (key == XK_space)
		print_map(game);
	return (0);
	(void)key, (void)game;
}

int	key_release_hook(int key, t_game *game)
{
	if (key == XK_Escape)
		mlx_loop_end(game->render.pmlx);
	return (0);
	(void)key, (void)game;
}
