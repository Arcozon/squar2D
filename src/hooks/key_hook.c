/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:40:04 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/30 13:29:55 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_press(const int key, uint64_t *f_key)
{
	if (key == XK_w || key == XK_W)
		*f_key |= HOOK_M_W;
	else if (key == XK_a || key == XK_A)
		*f_key |= HOOK_M_A;
	else if (key == XK_s || key == XK_S)
		*f_key |= HOOK_M_S;
	else if (key == XK_d || key == XK_D)
		*f_key |= HOOK_M_D;
	else if (key == XK_Right)
		*f_key |= HOOK_M_RARR;
	else if (key == XK_Left)
		*f_key |= HOOK_M_LARR;
	else if (key == XK_Up)
		*f_key |= HOOK_M_UARR;
	else if (key == XK_Down)
		*f_key |= HOOK_M_DARR;
}

void	handle_release(const int key, uint64_t *f_key)
{
	if (key == XK_w || key == XK_W)
		*f_key &= ~HOOK_M_W;
	else if (key == XK_a || key == XK_A)
		*f_key &= ~HOOK_M_A;
	else if (key == XK_s || key == XK_S)
		*f_key &= ~HOOK_M_S;
	else if (key == XK_d || key == XK_D)
		*f_key &= ~HOOK_M_D;
	else if (key == XK_Right)
		*f_key &= ~HOOK_M_RARR;
	else if (key == XK_Left)
		*f_key &= ~HOOK_M_LARR;
	else if (key == XK_Up)
		*f_key &= ~HOOK_M_UARR;
	else if (key == XK_Down)
		*f_key &= ~HOOK_M_DARR;
}

int	key_press_hook(int key, t_game *game)
{
	if (key == XK_Escape)
		mlx_loop_end(game->render.pmlx);
	else if (key == XK_e && game->any_doors)
		open_close_door(game);
	else
		handle_press(key, &game->f_keys);
	return (0);
}

int	key_release_hook(int key, t_game *game)
{
	if (key == XK_Escape)
		mlx_loop_end(game->render.pmlx);
	handle_release(key, &game->f_keys);
	return (0);
}
