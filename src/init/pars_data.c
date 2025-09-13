/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:18:41 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/13 15:39:30 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	pars_texture(t_pars *pars, char *line)
{
	const char	*key[] = {KEY_NORTH, KEY_EAST, KEY_SOUTH, KEY_WEST, 0};
	t_xpm_img	**textures;
	uint64_t	i;

	textures = (t_xpm_img *[]){&pars->no_texture, &pars->ea_texture,
		&pars->so_texture, &pars->we_texture};
	i = 0;
	while (key[i])
	{
		if (ft_str_space_cmp(line, key[i]))
		{
			if (textures[i]->p_img)
				return (ft_strlcpy(pars->err_context, key[i], BUFF_SIZE),
					pars->error = REDEFINED_TEXTURE);
			skip_key_space(&line);
			textures[i]->p_img = mlx_xpm_file_to_image(pars->pmlx.mlx_ptr,
					line, &textures[i]->width, &textures[i]->height);
			if (!textures[i]->p_img)
				return (ft_strlcpy(pars->err_context, line, BUFF_SIZE),
					pars->error = CANT_OPEN_TEXTURE);
			return (NO_ERR);
		}
		++i;
	}
	return (NO_ERR);
}

uint32_t	is_data_full(t_pars *pars)
{
	if (!pars->ceiling_defined || !pars->floor_defined)
	{
		ft_strlcpy(pars->err_context, "Ceiling", sizeof(pars->err_context));
		if (!pars->floor_defined)
			ft_strlcpy(pars->err_context, "Floor", sizeof(pars->err_context));
		return (pars->error = MISSING_COLOR);
	}
	if (!pars->ea_texture.p_img)
		ft_strlcpy(pars->err_context, "East", sizeof(pars->err_context));
	else if (!pars->we_texture.p_img)
		ft_strlcpy(pars->err_context, "West", sizeof(pars->err_context));
	else if (!pars->no_texture.p_img)
		ft_strlcpy(pars->err_context, "North", sizeof(pars->err_context));
	else if (!pars->so_texture.p_img)
		ft_strlcpy(pars->err_context, "South", sizeof(pars->err_context));
	else
		return (NO_ERR);
	return (pars->error = MISSING_TEXTURE);
}

uint32_t	pars_data(t_pars *pars)
{
	char	*line;

	while (!(pars->rd.flags & R_DONE) && !pars->error)
	{
		line = gnl(&pars->rd);
		skip_spaces(&line);
		if (!line || !line[0])
			continue ;
		if (is_color(line))
			pars_color(pars, line);
		else if (is_texture(line))
			pars_texture(pars, line);
		else if (is_map(line))
			break ;
		else
		{
			ft_strnlcpy(pars->err_context, line,
				sizeof(pars->err_context), index_strchr(line, ' '));
			return (pars->error = WRONG_KEY);
		}
	}
	if (pars->rd.error)
		pars->error = pars->rd.error;
	if (pars->error)
		return (pars->error);
	return (is_data_full(pars));
}
