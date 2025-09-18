/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 14:25:25 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/18 11:17:06 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	get_data_img(t_img *img, bool fill, int height)
{
	int	bpp;
	int	endian;
	int	linelen;

	img->p_data = (t_clr *)mlx_get_data_addr(img->p_img, &bpp,
			&linelen, &endian);
	if (fill)
	{
		bpp /= 8;
		img->width = linelen / bpp;
		img->height = height;
	}
	return (*img);
	(void)endian;
}

void	fill_render(t_pars *pars, t_render *render)
{
	render->f_clr = pars->color_floor;
	render->c_clr = pars->color_ceiling;
	render->mmap_d_closed = pars->mmap_d_closed;
	render->mmap_d_open = pars->mmap_d_open;
	render->mmap_player = pars->mmap_player;
	render->mmap_empty = pars->mmap_empty;
	render->mmap_wall = pars->mmap_wall;
	render->mmap_view = pars->mmap_view;
	render->pmlx = pars->pmlx.mlx_ptr;
	render->pwin = pars->pmlx.win_ptr;
	render->img.p_img = pars->pmlx.win_img;
	render->img_paa.p_img = pars->pmlx.win_img_paa;
	render->img_mmap.p_img = pars->pmlx.img_mmap;
	render->img_settings.p_img = pars->pmlx.img_settings;
	get_data_img(&render->img, 1, W_HEIGHT);
	get_data_img(&render->img_paa, 1, W_HEIGHT);
	get_data_img(&render->img_mmap, 1, MMAP_HEIGHT);
	get_data_img(&render->img_settings, 1, W_HEIGHT);
	render->n_txtr = get_data_img(&pars->no_texture, 0, 0);
	render->e_txtr = get_data_img(&pars->ea_texture, 0, 0);
	render->s_txtr = get_data_img(&pars->so_texture, 0, 0);
	render->w_txtr = get_data_img(&pars->we_texture, 0, 0);
}

void	fill_game(t_pars *pars, t_game *game)
{
	game->map = pars->resized_map;
	game->dim[X] = pars->dim[X];
	game->dim[Y] = pars->dim[Y];
	game->p_coo[X] = pars->player[X] + .5f;
	game->p_coo[Y] = pars->player[Y] + .5f;
	game->p_angle = pars->view_angle + pars->delta_angle;
	game->p_speed = PLAYER_BASE_SPEED;
	ft_memcpy(&game->doors, &pars->doors, sizeof(pars->doors));
	game->any_doors = pars->any_doors;
	game->fov = pars->fov;
	game->f_keys = 0;
	game->bonus = pars->bonus;
	fill_render(pars, &game->render);
}
