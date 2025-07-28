/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:22:26 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/28 16:35:01 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

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
	WRONG_FORMAT,
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

#endif
