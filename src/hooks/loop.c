/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 16:50:42 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/06 16:09:53 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	debug_key_pressed(t_game *game)
{
	static uint64_t		last_press;
	static const char	key_c[] = "WASDLR";

	// DEBUG("[%.3f|%.3f] (%.3f)\n", game->p_coo[X], game->p_coo[Y], game->p_angle);
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
	move_player(game);
	draw_frame(game, &game->render);	
	return (0);
}
