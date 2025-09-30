/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:18:17 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/30 18:25:19 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>

# include <time.h>

# include "mlx.h"

# include "types.h"
# include "errors.h"
# include "utils.h"

# include "parsing.h"
# include "hooks.h"
# include "render.h"
# include "raycasting.h"
# include "doors.h"

# define FOV_DELTA			0.014f
# define BASE_VANGLE_DELTA	0.013f
# define BASE_PLAYER_SPEED	0.01f
# define BASE_FOV			1.9f
# define BASE_SENSITIVITY	1.f

# define HALF_P_SIZE		0.2f

void	cub_mouse_hide(void *xvar, void *win, int hide);

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
	t_img	img_mmap;
	t_img	img_settings;

	t_img	n_txtr;
	t_img	e_txtr;
	t_img	s_txtr;
	t_img	w_txtr;
	t_img	door_txtr;

	t_clr	f_clr;
	t_clr	c_clr;

	t_clr	mmap_player;
	t_clr	mmap_empty;
	t_clr	mmap_wall;
	t_clr	mmap_view;
	t_clr	mmap_d_open;

	t_clr		fps_counter;
};

struct s_game
{
	float		p_coo[2];
	float		p_delta[2];
	float		p_angle;

	char		**map;
	float		dim[2];

	t_doors		doors;
	uint8_t		any_doors:1;

	float		fov;
	float		p_speed;

	float		angle_speed;
	float		sensitivity;

	int			mouse_coo[2];
	int			notify;
	int			focus;
	uint64_t	f_keys;

	uint64_t	frame_count;
	char		buffer_fps[BUFF_SIZE];
	uint64_t	len_buffer_fps;
	t_timespec	last_time;

	uint8_t		bonus:1;
	t_render	render;
};

struct s_cub
{
	uint8_t		bonus:1;
	t_pars		pars;

	t_game		game;

	char		*pname;
	t_err		error;
	char		err_context[BUFF_SIZE];
};

void	move_player(t_game *game);
void	check_colisions(const float p_coo[2], float p_delta[2],
			char *map[], const t_game *game);
void	colision_doors(const t_doors doors, const float coo[2],
			float p_delta[2], const int is_wall[2]);

#endif
