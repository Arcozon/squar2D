/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:25:42 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/28 12:42:23 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char *av[])
{
	char	test[200] =  "Salut a tous les amis, c est david lafarge pokemon";
	char	test2[200] = "";
	write(1, test, ft_strlen(test));
	write(1, "\n", 1);
	write(1, test2, ft_strlen(test2));
	write(1, "\n", 1);
	ft_memcpy(test2, test, 200);
	write(1, test, ft_strlen(test));
	write(1, "\n", 1);
	write(1, test2, ft_strlen(test2));
	write(1, "\n", 1);
	if (ac >= 2)
	{
		DEBUG("%lu", ft_strlen(av[1]));
		DEBUG("%s", ft_strendcmp(av[1], DOT_CUB) ? "Yes" : "NO")
	}
	(void)av;
}
