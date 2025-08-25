/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 14:25:25 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/25 16:37:30 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	get_data_img(t_img *img, bool fill, int height)
{
	int	bpp;
	int	endian;
	int	linelen;

	img->p_data = (t_clr *)mlx_get_data_addr(img->p_img, &bpp, &linelen, &endian);
	bpp /= 8;
	if (fill)
	{
		img->width = linelen / bpp;
		img->height = height;
	}
	(void)endian;
	return (*img);
}

void	fill_render(t_pars *pars, t_render *render)
{
	render->f_clr = pars->color_floor;
	render->c_clr = pars->color_ceiling;
	render->pmlx = pars->pmlx.mlx_ptr;
	render->pwin = pars->pmlx.win_ptr;
	render->img.p_img = pars->pmlx.win_img;
	render->img_paa.p_img = pars->pmlx.win_img_paa;
	get_data_img(&render->img, 1, W_HEIGHT);
	get_data_img(&render->img_paa, 1, W_HEIGHT);
	render->n_txtr = get_data_img(&pars->no_texture, 0, 0);
	render->e_txtr = get_data_img(&pars->ea_texture, 0, 0);
	render->s_txtr = get_data_img(&pars->so_texture, 0, 0);
	render->w_txtr = get_data_img(&pars->we_texture, 0, 0);
}

void	fill_game(t_pars *pars, t_game *game)
{
	game->map = pars->map;
	game->dim[X] = pars->dim[X];
	game->dim[Y] = pars->dim[Y];
	game->p_coo[Y] = pars->player[Y];
	game->p_coo[Y] = pars->player[Y];
	game->p_angle = pars->view_angle;
	game->p_speed = 0.001f;
	game->fov = 2 * M_PI / 3;
	game->f_keys = 0;
	fill_render(pars, &game->render);
}
