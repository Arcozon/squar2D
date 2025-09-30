/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_focus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:35:18 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/30 13:35:41 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	hook_enter_win(t_game *game)
{
	if (game->focus)
	{
		cub_mouse_hide(game->render.pmlx, game->render.pwin, 1);
		game->notify = mlx_mouse_get_pos(game->render.pmlx, game->render.pwin,
				&game->mouse_coo[X], &game->mouse_coo[Y]);
	}
	return (0);
}

int	hook_leave_win(t_game *game)
{
	if (game->focus)
	{
		cub_mouse_hide(game->render.pmlx, game->render.pwin, 0);
		game->notify = 0;
	}
	return (0);
}

int	hook_mouse_focus(int x, int y, t_game *game)
{
	if (game->notify && game->focus)
	{
		game->p_angle += game->sensitivity
			* game->angle_speed * (game->mouse_coo[X] - x);
		game->mouse_coo[X] = x;
		game->mouse_coo[Y] = x;
	}
	return (0);
	(void)y;
}

int	hook_focus_in(t_game *game)
{
	game->focus = 1;
	cub_mouse_hide(game->render.pmlx, game->render.pwin, 1);
	return (0);
	(void)game;
}

int	hook_focus_out(t_game *game)
{
	game->focus = 0;
	cub_mouse_hide(game->render.pmlx, game->render.pwin, 0);
	return (0);
	(void)game;
}
