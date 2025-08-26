/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 11:33:17 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/26 18:37:27 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_rectangle(t_img img_map, int start[2], int len[2], const t_clr color)
{
	t_clr	*pxl_start;
	int		iy;

	if (start[X] >= img_map.width)
		start[X] = img_map.width - 1;
	if (start[Y] >= img_map.height)
		start[Y] = img_map.height - 1;
	if (start[X] + len[X] > img_map.width)
		len[X] = img_map.width - start[X];
	if (start[Y] + len[Y] > img_map.height)
		len[Y] = img_map.height - start[Y];
	pxl_start = &img_map.p_data[start[X] + img_map.width * start[Y]];
	iy = 0;
	while (iy < len[Y])
	{
		ft_clrset(&pxl_start[iy * img_map.width], color, len[X]);
		++iy;
	}
}

static int	mmap_oob_or_wall(int ppx_coo[2], const float start[2], char **map, const float dim[2])
{
	const float	ppx_coo_map[2] = {start[X] + ppx_coo[X] * (MMAP_SQUARE_SIZE / (float)MMAP_WIDHT),
		start[Y] + ppx_coo[Y] * (MMAP_SQUARE_SIZE / (float)MMAP_HEIGHT)};

	if (ppx_coo_map[X] < 0 || ppx_coo_map[Y] < 0
		|| ppx_coo_map[X] + 1 > dim[X] || ppx_coo_map[Y] + 1 > dim[Y])
		return (1);
	if (map[(int)ppx_coo_map[X]][(int)ppx_coo_map[Y]] == WALL_CHAR)
		return (1);
	return (0);
}

static void	only_minimap(char **map, const float dim[2],
	t_img img_map, const float p_coo[2])
{
	const float	start[2] = {(p_coo[X] - MMAP_WIDHT / (float)MMAP_SQUARE_SIZE) / 2,
		(p_coo[Y] - MMAP_HEIGHT / (float)MMAP_SQUARE_SIZE) / 2};
	int			i[2];

	DEBUG("N_SQUARE: %f | %f", MMAP_WIDHT / (float)MMAP_SQUARE_SIZE, MMAP_HEIGHT / (float)MMAP_SQUARE_SIZE)
	DEBUG("START: %f | %f", start[X], start[Y])
	DEBUG("P_COO: %f | %f", p_coo[X], p_coo[Y])

	fill_rectangle(img_map, (int []){0, 0}, (int []){MMAP_WIDHT, MMAP_HEIGHT}, (t_clr){.rgb = MMAP_CLR_WALL});
	i[Y] = 0;
	while (i[Y] < MMAP_WIDHT)
	{
		i[X] = 0;
		while (i[X] < MMAP_HEIGHT)
		{
			if (!mmap_oob_or_wall(i, start, map, dim))
				img_map.p_data[i[X] + i[Y] * img_map.width].rgb = MMAP_CLR_WALL;
			++i[X];
		}
		++i[Y];
	}

	(void)map, (void)dim;
}

static void	mmap_player(t_img img_map, const float p_angle, const float fov)
{
	const int	center[] = {MMAP_WIDHT / 2, MMAP_HEIGHT / 2} ;
	int	ix;
	int	iy;

	iy = -MMAP_P_RADIUS;
	while (iy <= MMAP_P_RADIUS)
	{
		ix = -MMAP_P_RADIUS;
		while (ix <= MMAP_P_RADIUS)
		{
			if (ix * ix + iy *iy <= MMAP_P_RADIUS * MMAP_P_RADIUS)
			{
				img_map.p_data[center[X] + ix + (center[Y] + iy) * img_map.width].rgb = MMAP_CLR_PLAYR; 
			}
			++ix;
		}	
		++iy;
	}
	(void)p_angle, (void) fov;
}

void	render_minimap(t_game *game, t_render *render)
{
	only_minimap(game->map, game->dim, render->img_mmap, game->p_coo);
	mmap_player(render->img_mmap, game->p_angle, game->fov);
}
