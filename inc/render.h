/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:34:47 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/05 15:38:14 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "types.h"

# define BASE_COEF_AA		5
# define RANGE_ANTIALIASING	3

# define MMAP_XSTART		0
# define MMAP_YSTART		0
# define MMAP_SQUARE_SIZE	72
// # define MMAP_SQUARE_SIZE	40
# define MMAP_P_RADIUS		15
// # define MMAP_P_RADIUS		17
# define MMAP_CLR_VIEW		0xffff3a
# define MMAP_CLR_WALL		0x8f8f8f
# define MMAP_CLR_MTY		0x20af30
# define MMAP_CLR_PLAYR		0xff3a51

enum {R, G, B
};

void	set_floor_ceiling(t_render *render);
void	draw_p_wall(t_img txtr, t_render *render, int x_start, int x_end, int y_start, int y_end, float p_start, float p_end);

void	render_mmap_environement(char *map[], const float dim[2], const float p_coo[2], t_img mmap);
void	render_mmap_one_ray(t_game *game, t_col col);
void	render_minimap(t_game *game, t_render *render);

void	antialiasing_top(const t_clr pre_aa[], t_clr post_aa[], const t_clr c_clr);
void	antialiasing_bot(const t_clr pre_aa[], t_clr post_aa[], const t_clr f_clr);
void	antialiasing(t_render *render);
void	draw_frame(t_game *game, t_render *render);

void	check_colisions(t_game *game);

#endif
