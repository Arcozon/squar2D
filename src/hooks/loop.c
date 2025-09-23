/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 16:50:42 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/23 12:51:33 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	debug_key_pressed(t_game *game)
{
	static uint64_t		last_press;
	static const char	key_c[] = "WASDlrud";

	if (last_press != game->f_keys)
	{
		last_press = game->f_keys;
		if (last_press)
		{
			for(int i = 0; key_c[i]; ++i)
				if (last_press & (1 << i))
					fprintf(stderr, "%c", key_c[i]);
		}
		else
			fprintf(stderr, "none");
		fprintf(stderr, "\n");
	}
}

int	cub_loop(t_game *game)
{
	debug_key_pressed(game);
	if (game->any_doors)
		handle_doors(game->doors);
	move_player(game);
	check_colisions(game->p_coo, game->p_delta, game->map);
	draw_frame(game, &game->render);
	return (0);
}
