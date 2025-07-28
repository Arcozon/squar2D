/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:25:42 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/28 16:24:00 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_cub(t_cub *cub)
{
	
}



int	main(int ac, char *av[])
{
	__attribute__((cleanup(free_cub))) t_cub	cub;
	return (perror_cub(cub));
}
