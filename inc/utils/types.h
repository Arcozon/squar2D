/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 16:01:28 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/17 13:05:54 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdint.h>
# include <stdbool.h>

# define BUFF_SIZE		2048
# define N_HASH_DOORS	8

typedef uint32_t				t_err;

typedef struct s_mlx			t_mlx;
typedef struct s_xpm_img		t_xpm_img;
typedef struct s_xpm_img		t_img;

typedef union u_clr				t_clr;

union __attribute__((may_alias, packed)) u_clr
{
	uint32_t				rgb;

	struct __attribute__((packed)) {
		uint8_t	b;
		uint8_t	g;
		uint8_t	r;
		uint8_t	opac;
	}	s_mask;
};

typedef struct s_vector			t_vector;
typedef struct s_read			t_read;

typedef struct s_door*			t_doors[N_HASH_DOORS];
typedef struct s_door*			t_one_door;

typedef struct s_pars			t_pars;
typedef struct s_render			t_render;
typedef struct s_game			t_game;
typedef struct s_cub			t_cub;

typedef struct s_draw_col_wall	t_dcwall;
typedef struct s_ray			t_ray;

enum	e_hit
{
	no_hit = 0,
	hor_hit,
	ver_hit,
	corner_hit
};

enum	e_side
{
	north_side,
	east_side,
	south_side,
	west_side
};

void	free_cub(t_cub *cub);
void	free_strstr(char **strstr, const uint32_t size);

#endif
