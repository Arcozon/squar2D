/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 11:33:17 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/05 15:38:09 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

__attribute__((always_inline, nonnull(1), hot))
static inline void	*ft_fclrset(uint32_t *restrict img_data,
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
static inline void	mmap_fill_square(t_img img, int coo_x,
	int coo_y, uint32_t clr)
{
	int	size[2];
	int	iy;

	if (coo_x >= img.width || coo_y >= img.height
		|| coo_x <= -MMAP_SQUARE_SIZE || coo_y <= -MMAP_SQUARE_SIZE)
		return ;
	size[X] = MMAP_SQUARE_SIZE;
	size[Y] = MMAP_SQUARE_SIZE;
	if (coo_x < 0)
	{
		size[X] += coo_x;
		coo_x = 0;
	}
	if (coo_y < 0)
	{
		size[Y] += coo_y;
		coo_y = 0;
	}
	if (size[X] + coo_x > img.width)
		size[X] = img.width - coo_x;
	if (size[Y] + coo_y > img.height)
		size[Y] = img.height - coo_y;
	iy = -1;
	while (++iy < size[Y])
		ft_fclrset((uint32_t *)&img.p_data[(coo_y + iy) * img.width + coo_x],
			clr, size[X]);
}

void	render_mmap_environement(char *map[], const float dim[2],
	const float p_coo[2], t_img mm)
{
	const int	start_sqr_coo[2] = {MMAP_WIDHT / 2 - MMAP_SQUARE_SIZE
		* p_coo[X], MMAP_HEIGHT / 2 - MMAP_SQUARE_SIZE * p_coo[Y]};
	int			sqr_coo[2];
	int			ix;
	int			iy;

	ft_fclrset((uint32_t *)mm.p_data, MMAP_CLR_WALL, mm.height * mm.width);
	iy = -1;
	while (++iy < dim[Y])
	{
		ix = 0;
		sqr_coo[Y] = start_sqr_coo[Y] + iy * MMAP_SQUARE_SIZE;
		if (sqr_coo[Y] <= -MMAP_SQUARE_SIZE || sqr_coo[Y] >= mm.height)
			continue ;
		while (++ix < dim[X])
		{
			sqr_coo[X] = start_sqr_coo[X] + ix * MMAP_SQUARE_SIZE;
			if (sqr_coo[X] <= -MMAP_SQUARE_SIZE || sqr_coo[X] >= mm.width)
				continue ;
			else if (map[iy][ix] == MTY_CHAR)
				mmap_fill_square(mm, sqr_coo[X], sqr_coo[Y], MMAP_CLR_MTY);
		}
	}
}

static void	mmap_player(t_img img_map, const float p_angle, const float fov)
{
	static const int	center[] = {MMAP_WIDHT / 2, MMAP_HEIGHT / 2};
	int			ix;
	int			iy;

	iy = -MMAP_P_RADIUS;
	while (iy <= MMAP_P_RADIUS)
	{
		ix = -MMAP_P_RADIUS;
		while (ix <= MMAP_P_RADIUS)
		{
			if (ix * ix + iy * iy <= MMAP_P_RADIUS * MMAP_P_RADIUS)
			{
				img_map.p_data[center[X] + ix
					+ (center[Y] + iy) * img_map.width].rgb = MMAP_CLR_PLAYR;
			}
			++ix;
		}	
		++iy;
	}
	(void)p_angle, (void)fov;
}

void	render_minimap(t_game *game, t_render *render)
{
	render_mmap_environement(game->map, game->dim,
		game->p_coo, render->img_mmap);
	
	check_colisions(game);
	
	mmap_player(render->img_mmap, game->p_angle, game->fov);
}
