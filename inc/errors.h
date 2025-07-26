/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:22:26 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/26 18:22:21 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

enum
{
	NO_ERR,
	E_PARS,
	E_MLC,
	E_READ,
	E_MLX,
	E_WIN,
	E_IMG
};

enum
{
	MISSING_FILE = 1,
	NOT_DOT_CUB,
	CANT_OPN,
	WRONG_FORMAT,
	MISSING_COLOR,
	WRONG_FORMAT_COLOR,
	REDEFINED_COLOR,
	MISSING_IMAGE,
	REDEFINED_IMAGE,
	CANT_OPEN_IMAGE,
	TOO_MANY_PLAYER,
	UNCLOSED_MAP,
	UNKNOWN_CHAR
};

#endif
