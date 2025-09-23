/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 16:48:07 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/23 11:36:23 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	enter_win(t_game *game)
{
	if (game->focus)
	{
		DEBUG("IN");
		cub_mouse_hide(game->render.pmlx, game->render.pwin, 1);
		game->notify = mlx_mouse_get_pos(game->render.pmlx, game->render.pwin,
				&game->mouse_coo[X], &game->mouse_coo[Y]);
	}
	return (0);
}

int	leave_win(t_game *game)
{
	if (game->focus)
	{
		DEBUG("OUT");
		cub_mouse_hide(game->render.pmlx, game->render.pwin, 0);
		game->notify = 0;
	}
	return (0);
}

int	test_mouse(int x, int y, t_game *game)
{
	if (game->notify && game->focus)
	{
		game->p_angle += VANGLE_DELTA * (game->mouse_coo[X] - x);
		game->mouse_coo[X] = x;
		game->mouse_coo[Y] = x;
	}
	return (0);
	(void)y;
}

int	test_focus_in(t_game *game)
{
	DEBUG("FOCUS IN");
	game->focus = 1;
	cub_mouse_hide(game->render.pmlx, game->render.pwin, 1);
	return (0);
	(void)game;
}

int	test_focus_out(t_game *game)
{
	DEBUG("FOCUS OUT");
	game->focus = 0;
	cub_mouse_hide(game->render.pmlx, game->render.pwin, 0);
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
	mlx_hook(mlx->win_ptr, FocusIn, FocusChangeMask,
		test_focus_in, &cub->game);
	mlx_hook(mlx->win_ptr, FocusOut, FocusChangeMask,
		test_focus_out, &cub->game);
	mlx_loop_hook(mlx->mlx_ptr, cub_loop, &cub->game);
}
