/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmap_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:40:58 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/13 12:30:58 by gaeudes          ###   ########.fr       */
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
static inline void	__mmap_fill_square(t_img img, int coo_x,
	int coo_y, uint32_t clr)
{
	int	size[2];

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
	while (size[Y]--)
		ft_fclrset((uint32_t *)&img.p_data[(coo_y + size[Y])
			* img.width + coo_x], clr, size[X]);
}

__attribute__((flatten))
void	render_mmap_environement(char *map[], const float dim[2],
	const float p_coo[2], t_render *rdr)
{
	const int	start_sqr_coo[2] = {
		MMAP_WIDHT / 2 - MMAP_SQUARE_SIZE * p_coo[X],
		MMAP_HEIGHT / 2 - MMAP_SQUARE_SIZE * p_coo[Y]};
	int			sqr_coo[2];
	int			i[2];

	__ft_fclrset((uint32_t *)rdr->img_mmap.p_data, rdr->mmap_wall.rgb,
		rdr->img_mmap.height * rdr->img_mmap.width);
	i[Y] = 0;
	while (++i[Y] < dim[Y])
	{
		sqr_coo[Y] = start_sqr_coo[Y] + i[Y] * MMAP_SQUARE_SIZE;
		if (sqr_coo[Y] <= -MMAP_SQUARE_SIZE || sqr_coo[Y] >= rdr->img_mmap.height)
			continue ;
		i[X] = 0;
		while (++i[X] < dim[X])
		{
			sqr_coo[X] = start_sqr_coo[X] + i[X] * MMAP_SQUARE_SIZE;
			if (sqr_coo[X] <= -MMAP_SQUARE_SIZE
				|| sqr_coo[X] >= rdr->img_mmap.width)
				continue ;
			else if (map[i[Y]][i[X]] == MTY_CHAR)
				__mmap_fill_square(rdr->img_mmap, sqr_coo[X], sqr_coo[Y],
					rdr->mmap_empty.rgb);
		}
	}
}
