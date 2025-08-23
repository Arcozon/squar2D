/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:18:17 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/23 18:20:17 by gaeudes          ###   ########.fr       */
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

# define DOT_CUB	".cub"

# define W_WIDTH	1200
# define W_HEIGHT	800

# define R_DONE			0b1
# define R_LDONE		0b10
# define R_CUT_S_SPC	0b100
# define R_CUT_E_SPC	0b1000

# define PLAYER_CHARS	"NSWE"
# define MAP_CHARS		"01 NSWE"
# define WALL_CHAR		'1'
# define NB_TEXTURE		4

// For 2 dimension arrays representing a grid, they ll be called as tab[y][x]
// 	y being the line number / height
//	 x being the place in the line / lenght
enum	{X,Y
};

struct s_mlx
{
	char		title[BUFF_SIZE];

	void		*mlx_ptr;
	void		*win_ptr;
	void		*win_img;
	void		*win_img_paa;

	uint32_t	error;
	char		err_context[BUFF_SIZE];
};

struct s_xpm_img
{
	void	*p_img;
	t_clr	*p_data;
	int		width;
	int		height;
};

struct s_pars
{
	t_read		rd;

	t_xpm_img	no_texture;
	t_xpm_img	ea_texture;
	t_xpm_img	so_texture;
	t_xpm_img	we_texture;

	t_clr		color_ceiling;
	t_clr		color_floor;
	uint8_t		ceiling_defined;
	uint8_t		floor_defined;

	t_vector	vec_map;
	uint64_t	dim[2];
	uint64_t	player[2];
	float		view_angle;
	char		**map;

	t_mlx		pmlx;

	uint32_t	syscall_error;
	uint32_t	error;
	char		err_context[BUFF_SIZE];
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
