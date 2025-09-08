/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:34:47 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/08 15:03:15 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "types.h"

# define BASE_COEF_AA		5
# define RANGE_ANTIALIASING	3

# define MMAP_XSTART		0
# define MMAP_YSTART		0
# define MMAP_SQUARE_SIZE	20
# define MMAP_P_RADIUS		(MMAP_SQUARE_SIZE * 2) / 5
# define MMAP_CLR_VIEW		0xffff3a
# define MMAP_CLR_WALL		0x8f8f8f
# define MMAP_CLR_MTY		0x20af30
# define MMAP_CLR_PLAYR		0xff3a51

struct s_draw_col_wall
{
	t_img	wall_img;

	float	img_percent;
	int		x_img;

	float	distance;
	int		img_y_start;
	int		img_y_range;
	int		screen_y_start;
	int		screen_y_range;
};

enum {R, G, B
};

void	render_mmap_environement(char *map[], const float dim[2],
			const float p_coo[2], t_img mmap);
void	render_mmap_one_ray(t_game *game, t_ray ray);
void	render_minimap(t_game *game, t_render *render);

void	antialiasing_top(const t_clr pre_aa[], t_clr post_aa[],
			const t_clr c_clr);
void	antialiasing_bot(const t_clr pre_aa[], t_clr post_aa[],
			const t_clr f_clr);
void	antialiasing(t_render *render);

void	set_floor_ceiling(t_render *render);

void	cub_putimgtoimg(const t_img src, t_img dst, const int coo[2]);

void	draw_frame(t_game *game, t_render *render);

void	draw_col_wall(t_dcwall info, t_img screen_img,
			const int screen_x, t_img wall_img);

#endif
