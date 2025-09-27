/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:07:30 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/27 18:50:52 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# define ZERO_RANGE	0.000005f

# define SQRT_2_O_2 0.7071067f

struct s_ray
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

	t_doors		doors;
	uint8_t		any_doors;
};

typedef struct s_col	t_col;
struct s_col
{
	float	start_coo[2];

	float	coo[2];

	float	n_step[2];
	float	dist_n_step_2[2];
	float	tt_nstep[2];
	float	ratio2[2];

	int		dir[2];
	int		to_add[2];
	int		for_check[2];

	uint8_t	hit[2];
	uint8_t	done:1;

	float	p_delta[2];
	float	adjusted_pdelta[2];
};

void	__check_one_ray(t_ray *ray, char **map)__attribute__((flatten));
void	ray_casting(t_game *game);

#endif
