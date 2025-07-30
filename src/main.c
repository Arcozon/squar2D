/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:25:42 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/30 17:29:45 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char *av[])
{
	t_read	rd;
	ft_bzero(&rd, sizeof(rd));
	rd.flags = R_CUT_E_SPC | R_CUT_S_SPC;
	// rd.fd = open("test_read", O_RDONLY);
	rd.fd = open("Makefile", O_RDONLY);
	if (rd.fd < 0)
		return (2);
	gnl(&rd);
	gnl(&rd);
	gnl(&rd);
	// gnl(&rd);
	// gnl(&rd);

	// __attribute__((cleanup(free_cub))) t_cub cub;
	// // if (!init_cub(&cub, ac, av))
	// // {
	// // 	DEBUG("Succes");
	// // }
	// return (perror_cub(cub));
	(void)ac, (void)av;
}
