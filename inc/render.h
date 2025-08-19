/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:34:47 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/19 17:50:53 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "types.h"

void	set_floor_ceiling(t_render *render);
// void	draw_p_wall(t_img txtr, t_render *render, int x_start, int x_end, int y_start, int	y_end);
void	draw_p_wall(t_img txtr, t_render *render, int x_start, int x_end, int y_start, int y_end, float p_start, float p_end);

void	draw_frame(t_game *game);

#endif
