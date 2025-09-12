/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:22:26 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/12 16:59:37 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "types.h"

enum
{
	NO_ERR,
	E_MLC,
	E_READ,
	E_MLX,
	E_WIN,
	E_IMG,
	ERR_SYS_MAX
};

enum
{
	ERR_ARGS = ERR_SYS_MAX,
	NOT_DOT_CUB,
	CANT_OPN_MAP,
	WRONG_KEY,
	MISSING_COLOR,
	REDEFINED_COLOR,
	WRONG_FORMAT_COLOR,
	MISSING_TEXTURE,
	REDEFINED_TEXTURE,
	CANT_OPEN_TEXTURE,
	MISSING_MAP,
	MISSING_PLAYER,
	TOO_MANY_PLAYER,
	UNCLOSED_MAP,
	UNKNOWN_CHAR,
	ERR_PARS_MAX
};

uint32_t	perror_cub(t_cub cub);

#endif
