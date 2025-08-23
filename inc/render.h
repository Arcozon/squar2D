/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:34:47 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/23 17:39:06 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "types.h"

# define BASE_COEF			5
# define RANGE_ANTIALIASING	2

enum {R, G, B
};

void	set_floor_ceiling(t_render *render);
void	draw_p_wall(t_img txtr, t_render *render, int x_start, int x_end, int y_start, int y_end, float p_start, float p_end);

void	antialiasing_top(const t_clr pre_aa[], t_clr post_aa[], const t_clr c_clr);
void	antialiasing_bot(const t_clr pre_aa[], t_clr post_aa[], const t_clr f_clr);
void	antialiasing(t_render *render);
void	draw_frame(t_game *game);

#endif
