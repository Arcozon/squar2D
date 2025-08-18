/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 16:49:15 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/18 15:10:13 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

# include <X11/keysym.h>
# include <X11/X.h>

# include "types.h"

int		key_press_hook(int key, t_game *game);
int		key_release_hook(int key, t_game *game);
int		cub_loop(t_game *game);

void	setup_hooks(t_mlx *mlx, t_cub *cub);

#endif
