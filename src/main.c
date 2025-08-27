/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:25:42 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/27 16:58:51 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#define DEBUG_INIT

#include "cub3d.h"

int	main(int ac, char *av[])
{
	TIMER_START
	__attribute__((cleanup(free_cub))) t_cub cub;
	if (!init_cub(&cub, ac, av))
	{
		mlx_loop(cub.pars.pmlx.mlx_ptr);
	}
	TIMER_END
	return (perror_cub(cub));
}
