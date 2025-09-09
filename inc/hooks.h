/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 16:49:15 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/09 17:58:12 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

# include <X11/keysym.h>
# include <X11/X.h>

# include "types.h"

# define HOOK_M_W		0b1
# define HOOK_M_A		0b10
# define HOOK_M_S		0b100
# define HOOK_M_D		0b1000
# define HOOK_M_LARR	0b10000
# define HOOK_M_RARR	0b100000
# define HOOK_M_UARR	0b1000000
# define HOOK_M_DARR	0b10000000

int		key_press_hook(int key, t_game *game);
int		key_release_hook(int key, t_game *game);
int		cub_loop(t_game *game);

void	setup_hooks(t_mlx *mlx, t_cub *cub);

#endif
