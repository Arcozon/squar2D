/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:23:05 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/08 13:55:31 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>

# include "types.h"

# define STRLEN_LOW_MASK	0x01010101
# define STRLEN_HIGH_MASK	0x80808080

uint64_t	ft_strlen(const char str[])__attribute__ ((const, pure, nonnull));
bool		ft_strendcmp(const char str[],
				const char end[])__attribute__ ((const, pure, nonnull));
void		ft_strlcpy(char *dst, const char *src, uint64_t dst_size);
void		ft_strnlcpy(char *dst, const char *src, uint64_t dst_size, uint64_t src_size);
uint64_t	index_strchr(const char str[], const char find);
char		*ft_strchr(char str[], const char to_find);

void		*ft_calloc(uint64_t	size);
void		*ft_bzero(void *vptr, uint64_t size);
void		*ft_memcpy(void *dst, const void *src, uint64_t size);
bool		ft_memcpm(void *s1, void *s2, uint64_t n);

#endif
