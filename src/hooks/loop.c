/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 16:50:42 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/30 13:28:23 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cub_loop(t_game *game)
{
	if (game->any_doors)
		handle_doors(game->doors, game);
	move_player(game);
	draw_frame(game, &game->render);
	return (0);
}
