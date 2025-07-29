/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:18:17 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/29 14:30:36 by gaeudes          ###   ########.fr       */
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

# define W_HIGHT	800
# define W_LENGHT	1200

struct s_mlx
{
	char		title[BUFF_SIZE];

	void		*mlx_ptr;
	void		*winptr;
	void		*img;

	uint32_t	error;
	char		err_context[BUFF_SIZE];
};

struct s_pars
{
	int			fd_map;

	char		*no_texture;
	char		*ea_texture;
	char		*su_texture;
	char		*we_texture;

	uint32_t	color_ceiling;
	uint32_t	color_floor;

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

uint32_t	init_cub(t_cub *cub, int ac, char *av[]);

#endif
