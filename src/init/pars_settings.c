/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_settings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:08:02 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/23 13:40:20 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_err	__pars_read_decimals(uint32_t *i, char *line, t_pars *pars, float *p_sett)
{
	float 	pow10;

	pow10 = 10;
	if (line[*i] == ',' || line[*i] == '.')
	{
		++*i;
		if (!ft_isdigit(line[*i]))
			return (pars->error = WRONG_FORMAT_FLOAT);
		while (ft_isdigit(line[*i]))
		{
			*p_sett += (line[*i] - '0') / pow10;
			pow10 *= 10;
			++*i;
		}
	}
	return (NO_ERR);
}

t_err	pars_read_float(float *p_sett, char *line, t_pars *pars)
{
	uint32_t	i;
	float 		sign;

	ft_strlcpy(pars->err_context, line, sizeof(pars->err_context));
	i = 0;
	sign = 1;
	*p_sett = 0.f;
	if (line[0] == '-')
		sign = (++i, -1);
	if (!ft_isdigit(line[i]))
		return (pars->error = WRONG_FORMAT_FLOAT);
	while (ft_isdigit(line[i]))
		*p_sett = *p_sett * 10 + line[i++] - '0';
	if (__pars_read_decimals(&i, line, pars, p_sett))
		return (pars->error = WRONG_FORMAT_FLOAT);
	if (line[i])
		return (pars->error = WRONG_FORMAT_FLOAT);
	*p_sett *= sign;
	return (pars->err_context[0] = '\0', NO_ERR);
}

t_err	pars_settings_bonus(t_pars *pars, char line[])
{
	static const char	*keys[] = {KEY_FOV, KEY_PLR_TETA,
		KEY_SPD_PLR, KEY_SPD_TETA, KEY_SPD_MOUSE, 0};
	float	 			**ptrs_settings;
	uint32_t			i;

	ptrs_settings = (float *[]){&pars->fov, &pars->delta_angle,
		&pars->p_speed, &pars->angle_speed, &pars->sensitivity};
	i = 0;
	while (keys[i])
	{
		if (ft_str_space_cmp(line, keys[i]))
		{
			skip_key_space(&line);
			return (pars_read_float(ptrs_settings[i], line, pars));
		}
		++i;
	}
	return (NO_ERR); 
}
