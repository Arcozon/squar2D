/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:22:43 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/30 14:12:37 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdint.h>
# include <stdbool.h>

typedef struct s_img	t_img;
typedef struct s_mlx	t_mlx;

typedef struct s_read	t_read;

typedef struct s_pars	t_pars;
typedef struct s_cub	t_cub;

void	free_cub(t_cub *cub);

#endif
