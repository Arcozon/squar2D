/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_doors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 12:53:07 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/20 15:05:46 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

__attribute__((always_inline, nonnull(1), hot))
static inline void	*__ft_fclrset(uint32_t *restrict img_data,
	const uint32_t color, const uint64_t size)
{
	uint64_t	i;

	i = 0;
	while (i < size)
	{
		img_data[i] = color;
		++i;
	}
	return (img_data);
}

__attribute__((always_inline))
static inline void	__mmap_fill_rect(t_img img, int coo[2],
	int dim[2], const uint32_t clr)
{
	if (coo[X] < 0)
	{
		dim[X] -= -coo[X];
		coo[X] = 0;
	}
	else if (coo[X] + dim[X] >= img.width)
		dim[X] = img.width - coo[X];
	if (coo[Y] < 0)
	{
		dim[Y] -= -coo[Y];
		coo[Y] = 0;
	}
	else if (coo[Y] + dim[Y] >= img.height)
		dim[Y] = img.height - coo[Y];
	
	while (dim[Y]--)
		__ft_fclrset((uint32_t *)&img.p_data[(coo[Y] + dim[Y])
			* img.width + coo[X]], clr, dim[X]);
}

__attribute__((always_inline, flatten))
static inline bool	__get_door_coo(t_c_door door, const float p_coo[2],
	int rect_coo[2], int rect_dim[2])
{
	rect_dim[X] = MMAP_SQUARE_SIZE;
	rect_dim[Y] = MMAP_SQUARE_SIZE;
	if (door->e_or == D_OR_HOR)
		rect_dim[X] = MMAP_SQUARE_SIZE * door->closed_percent;
	else
		rect_dim[Y] = MMAP_SQUARE_SIZE * door->closed_percent;
	rect_coo[X] = (MMAP_WIDHT / 2) + (door->x - p_coo[X]) * MMAP_SQUARE_SIZE;
	rect_coo[Y] = (MMAP_HEIGHT / 2) + (door->y - p_coo[Y]) * MMAP_SQUARE_SIZE;
	return ((rect_coo[X] + rect_dim[X] >= 0 && rect_coo[X] < MMAP_WIDHT)
		&& (rect_coo[Y] + rect_dim[Y] >= 0 && rect_coo[Y] < MMAP_HEIGHT));
}

__attribute__((flatten))
void	mmap_doors(const t_doors doors, t_img mmap, 
	const float p_coo[2], const t_clr d_clr)
{
	int			rect_coo[2];
	int			rect_dim[2];
	t_c_door	one_door;
	uint32_t	i;

	i = 0;
	for (int i = 0; i < N_HASH_DOORS; ++i)
	{
		one_door = doors[i];
		while (one_door)
		{
			if (__get_door_coo(one_door, p_coo, rect_coo, rect_dim))
				__mmap_fill_rect(mmap, rect_coo, rect_dim, d_clr.rgb);
			// DEBUG("Coo %d | %d", rect_coo[X], rect_coo[Y]);
			// DEBUG("Dim %d | %d", rect_dim[X], rect_dim[Y]);
			one_door = one_door->next;
		}
	}
	// WAIT
}
