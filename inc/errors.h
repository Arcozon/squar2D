/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:22:26 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/26 12:22:23 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

enum
{
	NO_ERR,
	E_MLC,
	E_OPN,
	E_READ,
	E_MLX,
	E_WIN,
	E_IMG
};

enum
{
	NOT_DOT_CUB = 1,
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
