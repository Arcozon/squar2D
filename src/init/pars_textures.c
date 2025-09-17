/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:25:11 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/17 19:13:17 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

__attribute__((always_inline))
uint32_t	__pars_texture(t_pars *pars, char *line, const char *keys[],
	t_xpm_img	*ptxtrs[])
{
	uint64_t	i;

	i = 0;
	while (keys[i])
	{
		if (ft_str_space_cmp(line, keys[i]))
		{
			if (ptxtrs[i]->p_img)
				return (ft_strlcpy(pars->err_context, keys[i], BUFF_SIZE),
					pars->error = REDEFINED_TEXTURE);
			skip_key_space(&line);
			ptxtrs[i]->p_img = mlx_xpm_file_to_image(pars->pmlx.mlx_ptr,
					line, &ptxtrs[i]->width, &ptxtrs[i]->height);
			if (!ptxtrs[i]->p_img)
				return (ft_strlcpy(pars->err_context, line, BUFF_SIZE),
					pars->error = CANT_OPEN_TEXTURE);
			return (NO_ERR);
		}
		++i;
	}
	return (NO_ERR);
}

uint32_t	pars_texture(t_pars *pars, char *line)
{
	const char	*keys[] = {KEY_NORTH, KEY_EAST, KEY_SOUTH, KEY_WEST, 0};
	t_xpm_img	**ptxtrs;

	ptxtrs = (t_xpm_img *[]){&pars->no_texture, &pars->ea_texture,
		&pars->so_texture, &pars->we_texture};
	return (__pars_texture(pars, line, keys, ptxtrs));
}

uint32_t	pars_texture_bonus(t_pars *pars, char *line)
{
	const char	*keys[] = {KEY_NORTH, KEY_EAST, KEY_SOUTH,
		KEY_WEST, KEY_DOOR, 0};
	t_xpm_img	**ptxtrs;

	ptxtrs = (t_xpm_img *[]){&pars->no_texture, &pars->ea_texture,
		&pars->so_texture, &pars->we_texture, &pars->door_texture};
	return (__pars_texture(pars, line, keys, ptxtrs));
}
