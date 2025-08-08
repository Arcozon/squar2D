/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 16:48:07 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/08 17:01:29 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	setup_hooks(t_mlx *mlx, t_cub *cub)
{
	mlx_hook(mlx->win_ptr, KeyPress, KeyPressMask, key_press_hook, cub);
	mlx_hook(mlx->win_ptr, KeyRelease, KeyReleaseMask, key_release_hook, cub);
	mlx_hook(mlx->win_ptr, DestroyNotify, 0, mlx_loop_end, mlx->mlx_ptr);
	mlx_loop_hook(mlx->mlx_ptr, cub_loop, cub);
}

// mlx_hook(imlx->win_ptr, XHOOK_MOUSEDOWN, ButtonPressMask,
// 	hook_mouse_press, fdf);
// mlx_hook(imlx->win_ptr, XHOOK_MOUSEUP, ButtonReleaseMask,
// 	hook_mouse_release, fdf);
// mlx_hook(imlx->win_ptr, XHOOK_MOUSEMOVE,
// 	Button1MotionMask | Button3MotionMask, hook_mouse_move, fdf);
