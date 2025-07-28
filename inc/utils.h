/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:23:05 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/28 11:29:57 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "types.h"

# define STRLEN_LOW_MASK	0x01010101
# define STRLEN_HIGH_MASK	0x80808080

uint64_t	ft_strlen(char str[]);
bool		ft_strendcmp(char str[], char end[]);
void		*ft_bzero(void *vptr, uint64_t size);
void		*ft_memcpy(void *dst, void *src, uint64_t size);

#endif
