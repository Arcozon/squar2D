/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:35:10 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/23 17:33:10 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	antialiasing(t_render *render)
{
	ft_memcpy(render->img_paa.p_data, render->img.p_data,
		sizeof(t_clr) * W_HEIGHT * W_WIDTH);
	antialiasing_top(render->img.p_data, render->img_paa.p_data, render->c_clr);
	antialiasing_bot(render->img.p_data, render->img_paa.p_data, render->f_clr);
}
