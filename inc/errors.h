/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:22:26 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/29 12:26:29 by gaeudes          ###   ########.fr       */
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
	E_IMG
};

enum
{
	ERR_ARGS = 1,
	NOT_DOT_CUB,
	CANT_OPN_MAP,
	WRONG_KEY,
	MISSING_COLOR,
	REDEFINED_COLOR,
	WRONG_FORMAT_COLOR,
	MISSING_TEXTURE,
	REDEFINED_TEXTURE,
	CANT_OPEN_TEXTURE,
	TOO_MANY_PLAYER,
	UNCLOSED_MAP,
	UNKNOWN_CHAR
};

uint32_t	perror_cub(t_cub cub);

#endif
