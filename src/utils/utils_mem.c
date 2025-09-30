/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:19:48 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/30 13:28:12 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*ft_bzero(void *ptr, uint64_t size)
{
	const uintptr_t	ptr_mask = sizeof(uint64_t) - 1;
	uint8_t			*ptr_8;
	uint64_t		*ptr_64;
	uint64_t		size_long;
	uint64_t		i;

	ptr_8 = ptr;
	i = 0;
	while ((uint64_t)ptr_8 & ptr_mask && i < size)
		ptr_8[i++] = 0;
	size -= i;
	ptr_8 += i;
	size_long = size >> 3;
	size &= ptr_mask;
	ptr_64 = (uint64_t *)ptr_8;
	ptr_8 += sizeof(*ptr_64) * size_long;
	i = 0;
	while (i < size_long)
		ptr_64[i++] = 0;
	i = 0;
	while (i < size)
		ptr_8[i++] = 0;
	return (ptr);
}

void	*ft_memset(void *ptr, uint64_t size, const uint64_t set)
{
	const uint64_t	set_64 = set | set << 8 | set << 16 | set << 24 | set << 32
		| set << 40 | set << 48 | set << 56;
	const void		*cpy_ptr = ptr;
	uint64_t		*ptr_64;
	uint64_t		i;
	uint64_t		size_64;

	while (size && (uintptr_t)ptr & sizeof(uint64_t) - 1)
		*(uint8_t *)ptr++ = (--size, set);
	ptr_64 = ptr;
	i = 0;
	size_64 = size >> 3;
	size &= sizeof(uint64_t) - 1;
	while (i < size_64)
	{
		ptr_64[i] = set_64;
		++i;
	}
	ptr = &ptr_64[i];
	while (size)
	{
		--size;
		*(uint8_t *)ptr++ = set;
	}
	return ((void *)cpy_ptr);
}

void	*ft_memcpy(void *dst, const void *src, uint64_t size)
{
	const uintptr_t	ptr_mask = sizeof(uint64_t) - 1;
	const uint64_t	*lu_src;
	uint64_t		*lu_dst;
	uint32_t		i;

	if (!src)
		return (0);
	while (size && ((uintptr_t)src & ptr_mask))
	{
		--size;
		*(uint8_t *)(dst++) = *(uint8_t *)(src++);
	}
	lu_dst = dst;
	lu_src = src;
	src += size & ~ptr_mask;
	dst += size & ~ptr_mask;
	i = size >> 3;
	while (i--)
		lu_dst[i] = lu_src[i];
	size &= ptr_mask;
	while (size--)
		*(uint8_t *)(dst++) = *(uint8_t *)(src++);
	return (dst - size);
}
