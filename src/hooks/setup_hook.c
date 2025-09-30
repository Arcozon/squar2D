/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 16:48:07 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/30 13:42:18 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	setup_hooks(t_mlx *mlx, t_cub *cub)
{
	mlx_hook(mlx->win_ptr, KeyPress, KeyPressMask,
		key_press_hook, &cub->game);
	mlx_hook(mlx->win_ptr, KeyRelease, KeyReleaseMask,
		key_release_hook, &cub->game);
	mlx_hook(mlx->win_ptr, DestroyNotify, None,
		mlx_loop_end, mlx->mlx_ptr);
	mlx_hook(mlx->win_ptr, EnterNotify, EnterWindowMask,
		hook_enter_win, &cub->game);
	mlx_hook(mlx->win_ptr, LeaveNotify, LeaveWindowMask,
		hook_leave_win, &cub->game);
	mlx_hook(mlx->win_ptr, MotionNotify, PointerMotionMask,
		hook_mouse_focus, &cub->game);
	mlx_hook(mlx->win_ptr, FocusIn, FocusChangeMask,
		hook_focus_in, &cub->game);
	mlx_hook(mlx->win_ptr, FocusOut, FocusChangeMask,
		hook_focus_out, &cub->game);
	mlx_loop_hook(mlx->mlx_ptr, cub_loop, &cub->game);
}
