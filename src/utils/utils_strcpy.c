/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_strcpy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:12:28 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/30 13:20:52 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

__attribute__((flatten, nonnull))
void	ft_strlcat(char *dst, const char *src, uint64_t dst_size)
{
	const uint64_t	dst_end = ft_strlen(dst);

	ft_strlcpy(dst + dst_end, src, dst_size - dst_end);
}

__attribute__((flatten, nonnull))
void	ft_strlcpy(char *dst, const char *src, uint64_t dst_size)
{
	uint64_t	f_size;

	if (!dst_size)
		return ;
	f_size = heap_strlen(src);
	if (f_size >= dst_size)
		f_size = dst_size - 1;
	ft_memcpy(dst, src, f_size);
	dst[f_size] = 0;
}

__attribute__((flatten, nonnull))
void	ft_strnlcpy(char *dst, const char *src,
	uint64_t dst_size, uint64_t src_size)
{
	uint64_t	f_size;

	f_size = src_size;
	if (!dst_size)
		return ;
	if (f_size >= dst_size)
		f_size = dst_size - 1;
	ft_memcpy(dst, src, f_size);
	dst[f_size] = 0;
}

__attribute__((flatten, nonnull))
void	ft_lutoacpy(const uint64_t nb, char str[], const uint64_t size)
{
	uint64_t	i;
	uint64_t	pow;

	pow = 10;
	i = 0;
	while (nb / pow)
		pow *= 10;
	while (pow / 10 && i < size - 1)
	{
		pow /= 10;
		str[i] = nb / pow % 10 + '0';
		++i;
	}
	str[i] = '\0';
}
