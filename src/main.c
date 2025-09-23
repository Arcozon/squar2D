/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:25:42 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/23 11:36:41 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define DEBUG_INIT
#include "cub3d.h"

int	main(int ac, char *av[])
{
	__attribute__((cleanup(free_cub))) t_cub cub;
	TIMER_START;
	if (!init_cub(&cub, ac, av))
		mlx_loop(cub.pars.pmlx.mlx_ptr);
	TIMER_END;
	cub_mouse_hide(cub.pars.pmlx.mlx_ptr, cub.pars.pmlx.win_ptr, 0);
	return (perror_cub(cub));
}
