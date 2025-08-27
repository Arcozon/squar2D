/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 12:05:33 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/27 13:43:06 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_render_mmap
{
	float	start_x;
	float	start_y;
	float	offset_x;
	float	offset_y;

	float	n_square_x;
	float	n_square_y;

	float	first_pxl_x;
	float	first_pxl_y;

	int		coo_fpxl_x;
	int		coo_fpxl_y;
}	t_rmmap;

// void	fill_render_mmap(t_rmmap *r_mmap, const float p_coo[2])
// {
// 	ft_bzero(r_mmap, sizeof(*r_mmap));
// 	r_mmap->n_square_x = MMAP_WIDHT / (float)MMAP_SQUARE_SIZE;
// 	r_mmap->n_square_y = MMAP_HEIGHT / (float)MMAP_SQUARE_SIZE;
// 	r_mmap->coo_fpxl_x = (int)(p_coo[X] - r_mmap->n_square_x / 2);
// 	r_mmap->coo_fpxl_y = (int)(p_coo[Y] - r_mmap->n_square_y / 2);
// 	if (r_mmap->coo_fpxl_x < 0)
// 		r_mmap->coo_fpxl_x = 0;
// 	if (r_mmap->coo_fpxl_y < 0)
// 		r_mmap->coo_fpxl_y = 0;
// 	r_mmap->first_pxl_y = ;
	
// }


// void	minimap_back(char *map[], const float dim[2], const float p_coo[2], t_img mmap)
// {
// 	// t_rmmap	r_mmap;

// 	// fill_render_mmap(&r_mmap, dim, p_coo);
// }

__attribute__((always_inline))
static inline void	mmap_fill_square(t_img img, int coo_x, int coo_y,  t_clr clr)
{
	int size[2];
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
		// DEBUG("sizeY = %d", size[Y])
	}
	if (size[X] + coo_x > img.width)
		size[X] = img.width - coo_x;
	if (size[Y] + coo_y > img.height)
		size[Y] = img.height - coo_y;
	// DEBUG("--{%d, %d}, (%d, %d)", coo_x, coo_y, size[X], size[Y])
	iy = -1;
	while (++iy < size[Y])
		ft_clrset(&img.p_data[(coo_y + iy) * img.width + coo_x], clr, size[X]);
}

void	render2_minimap(char *map[], const float dim[2], const float p_coo[2], t_img mmap)
{
	const int	start_sqr_coo[2] = {MMAP_WIDHT / 2 - MMAP_SQUARE_SIZE * p_coo[X],
		MMAP_HEIGHT / 2 - MMAP_SQUARE_SIZE * p_coo[Y]};
	int	sqr_coo[2];
	int	ix;
	int	iy;

	// DEBUG("start coo [%d|%d]", start_sqr_coo[X], start_sqr_coo[Y]) WAIT
	ft_clrset(mmap.p_data, (t_clr){.rgb = MMAP_CLR_WALL}, mmap.height * mmap.width);

	iy = -1;
	while (++iy < dim[Y])
	{
		ix =  0;
		// DEBUG("[XY] %d %d", ix, iy)
		sqr_coo[Y] = start_sqr_coo[Y] + iy * MMAP_SQUARE_SIZE;
		if (sqr_coo[Y] <= -MMAP_SQUARE_SIZE || sqr_coo[Y] >= mmap.height)
			continue ;
		// DEBUG("COO_Y: %d", sqr_coo[Y]);
		while (++ix < dim[X])
		{
			sqr_coo[X] = start_sqr_coo[X] + ix * MMAP_SQUARE_SIZE;
			if (sqr_coo[X] <= -MMAP_SQUARE_SIZE || sqr_coo[X] >= mmap.width)
				continue ;
			else if (map[iy][ix] == MTY_CHAR)
			{

				// DEBUG("-COO_X: %d  [%d|%d](%c)", sqr_coo[X], ix, iy, map[iy][ix])
				mmap_fill_square(mmap, sqr_coo[X], sqr_coo[Y], (t_clr){MMAP_CLR_MTY});
			}
			
		}
	}
	// WAIT
}
