/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:18:17 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/25 16:04:40 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>

# include "mlx.h"

# include "types.h"
# include "errors.h"
# include "utils.h"

# include "parsing.h"
# include "hooks.h"
# include "render.h"

// For 2 dimension arrays representing a grid, they ll be called as tab[y][x]
// 	y being the line number / height
//	 x being the place in the line / lenght
enum	{X,Y
};

struct s_render
{
	void	*pmlx;
	void	*pwin;
	t_img	img;
	t_img	img_paa;

	t_img	n_txtr;
	t_img	e_txtr;
	t_img	s_txtr;
	t_img	w_txtr;

	t_clr	f_clr;
	t_clr	c_clr;
};

struct s_game
{
	float		p_coo[2];
	float		p_angle;

	char		**map;
	float		dim[2];

	float		fov;

	uint64_t	f_keys;

	t_render	render;
};

struct s_cub
{
	t_pars		pars;

	t_game		game;

	char		*pname;
	uint32_t	error;
	char		err_context[BUFF_SIZE];
};

uint32_t	init_cub(t_cub *cub, int ac, char *av[]);

#endif
