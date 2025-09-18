/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:56:57 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/18 16:56:58 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOORS_H
# define DOORS_H

# include "types.h"

# define PRIME_HASH_DOOR	829

# define RADIUS_DOOR_OPEN	1.5f

# define VALUE_DOOR_OPEN	0.0f
# define VALUE_DOOR_CLOSED	1.0f
# define DOOR_SPEED			0.01f

struct	s_door
{
	int				x;
	int				y;

	float			closed_percent;
	uint8_t			open:1;
	enum	{
		D_IDLE,
		D_OPENING,
		D_CLOSING
	}	e_status;

	struct s_door	*next;
};

t_err		add_door(t_doors doors, const int x, const int y);
uint32_t	hash_door(const int a, const int b);

t_one_door	find_door(const t_doors doors, const int x, const int y);
void		free_doors(t_doors doors);

void		handle_doors(t_doors doors);
void		call_all_doors(t_doors doors, t_game *game,
				void (*fct_door)(t_one_door, t_game *));

void	open_close_door(t_game *game);


#endif
