/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:07:30 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/05 15:38:54 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# define ZERO_RANGE	0.000005f



typedef struct	s_col
{
	float	f_coo[2];
	int		i_coo[2];
	float	next_step[2];
	float	distance_next_step[2];

	float	teta_step;
	float	teta;
	float	slope;
	float	sin_t;
	int		is_sin_null;
	float	cos_t;
	int		is_cos_null;
	
	float	d_nextint[2];
	int		dir[2];
	int		add_thing[2];

	int		for_check[2];

	enum e_hit	hit;
	float		percent;
	float		distance;
}	t_col;

#endif
