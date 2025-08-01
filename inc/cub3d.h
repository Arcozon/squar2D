/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:18:17 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/01 15:39:21 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# include "mlx.h"

# include "types.h"
# include "errors.h"
# include "utils.h"

# define DOT_CUB	".cub"
# define BUFF_SIZE	2048

# define W_WIDTH	1200
# define W_HEIGHT	800

# define R_DONE			0b1
# define R_LDONE		0b10
# define R_CUT_S_SPC	0b100
# define R_CUT_E_SPC	0b1000

# define MAP_CHARS		"01 NSWE"

struct s_read
{
	int			fd;
	int 		br;
	char		content[BUFF_SIZE];
	
	char		*line;
	uint8_t		flags;
	uint32_t	error;
};

struct s_mlx
{
	char		title[BUFF_SIZE];

	void		*mlx_ptr;
	void		*win_ptr;
	void		*win_img;

	uint32_t	error;
	char		err_context[BUFF_SIZE];
};

struct s_pars
{
	t_read		rd;

	char		*no_texture;
	char		*ea_texture;
	char		*su_texture;
	char		*we_texture;

	uint32_t	color_ceiling;
	uint32_t	color_floor;
	uint8_t		ceiling_defined;
	uint8_t		floor_defined;

	char		**map;
	t_mlx		pmlx;

	uint32_t	error;
	char		err_context[BUFF_SIZE];
};

struct s_cub
{
	t_pars		pars;

	char		*pname;
	uint32_t	error;
	char		err_context[BUFF_SIZE];
};

char	*gnl(t_read *rd);

uint32_t	init_cub(t_cub *cub, int ac, char *av[]);
uint32_t	parsing(t_pars *pars);

#endif
