/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:07:30 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/08 13:13:43 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# define ZERO_RANGE	0.000005f

struct s_col
{
	float		f_coo[2];
	int			i_coo[2];
	float		n_step[2];
	float		dist_n_step[2];

	float		teta_step;
	float		teta;
	float		sin_t;
	int			is_sin_null;
	float		cos_t;
	int			is_cos_null;

	int			dir[2];
	int			add_thing[2];
	int			for_check[2];

	enum e_hit	hit;
	enum e_side	side;
	float		percent;
	float		distance;
};

void	check_colisions(t_game *game);

#endif
