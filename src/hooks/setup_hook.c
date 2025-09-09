/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 16:48:07 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/09 18:03:51 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	enter_win(t_game *game)
{
	cub_mouse_hide(game->render.pmlx, game->render.pwin, 1);
	game->notify_focus = mlx_mouse_get_pos(game->render.pmlx, game->render.pwin,
			&game->mouse_coo[X], &game->mouse_coo[Y]);
	DEBUG("ON [%d] %d|%d", game->notify_focus,
		game->mouse_coo[X], game->mouse_coo[Y]);
	return (0);
}

int	leave_win(t_game *game)
{
	cub_mouse_hide(game->render.pmlx, game->render.pwin, 0);
	game->notify_focus = 0;
	return (0);
}

int	test_mouse(int x, int y, t_game *game)
{
	DEBUG("%d | %d", x, y);
	if (game->notify_focus)
	{
		game->p_angle += VANGLE_DELTA * (game->mouse_coo[X] - x);
		game->mouse_coo[X] = x;
		game->mouse_coo[Y] = x;
	}
	return (0);
	(void)game;
}

void	setup_hooks(t_mlx *mlx, t_cub *cub)
{
	mlx_hook(mlx->win_ptr, KeyPress, KeyPressMask,
		key_press_hook, &cub->game);
	mlx_hook(mlx->win_ptr, KeyRelease, KeyReleaseMask,
		key_release_hook, &cub->game);
	mlx_hook(mlx->win_ptr, DestroyNotify, None,
		mlx_loop_end, mlx->mlx_ptr);
	mlx_hook(mlx->win_ptr, MotionNotify, PointerMotionMask,
		test_mouse, &cub->game);
	mlx_hook(mlx->win_ptr, EnterNotify, EnterWindowMask,
		enter_win, &cub->game);
	mlx_hook(mlx->win_ptr, LeaveNotify, LeaveWindowMask,
		leave_win, &cub->game);
	mlx_hook(mlx->win_ptr, MotionNotify, PointerMotionMask,
		test_mouse, &cub->game);
	mlx_loop_hook(mlx->mlx_ptr, cub_loop, &cub->game);
}
