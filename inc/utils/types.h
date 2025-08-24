/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 16:01:28 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/24 11:14:17 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdint.h>
# include <stdbool.h>

# define BUFF_SIZE	2048

typedef struct s_xpm_img	t_xpm_img;
typedef struct s_xpm_img	t_img;

typedef union u_clr			t_clr;
union __attribute__((packed, may_alias)) u_clr{
	uint32_t				rgb;
	struct __attribute__((packed)) {
		uint8_t	b;
		uint8_t	g;
		uint8_t	r;
		uint8_t	unused;
	}	s_mask;
};

typedef struct s_mlx		t_mlx;

typedef struct s_vector		t_vector;
typedef struct s_read		t_read;

typedef struct s_pars		t_pars;
typedef struct s_cub		t_cub;
typedef struct s_game		t_game;
typedef struct s_render		t_render;

void	free_cub(t_cub *cub);

#endif
