/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:29:01 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/31 14:54:13 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "debug.h"

__attribute__ ((const, pure, nonnull))
uint64_t	ft_strlen(const char str[])
{
	const char		*start = str;
	uint64_t		*aligned_ptr;

	while (*str && (uintptr_t)str & (sizeof(uintptr_t) - 1))
		++str;
	aligned_ptr = (uint64_t *)str;
	while ((*aligned_ptr - STRLEN_LOW_MASK)
		& ~(*aligned_ptr) & STRLEN_HIGH_MASK == 0)
		++aligned_ptr;
	str = (char *)aligned_ptr;
	while (*str)
		++str;
	return (str - start);
}

__attribute__ ((const, pure, nonnull))
bool	ft_strendcmp(const char str[], const char end[])
{
	const uint64_t	str_len = ft_strlen(str);	
	const uint64_t	str_end = ft_strlen(end);	
	uint64_t		i;

	i = 0;
	if (str_len < str_end)
		return (false);
	while (i <= str_end)
	{
		if (str[str_len - i] != end[str_end - i])
			return (false);
		++i;
	}
	return (true);
}

void	*ft_bzero(void *vptr, uint64_t size)
{
	char	*ptr;

	ptr = vptr;
	while ((uint64_t)ptr & 0b111 && size)
	{
		*ptr = 0;
		++ptr;
		--size;
	}
	while (size & ~0b111)
	{
		*(uint64_t *)ptr = 0;
		ptr += 8;
		size -= 8;
	}
	while (size)
	{
		*ptr = 0;
		++ptr;
		--size;
	}
	return (vptr);
}

void	*ft_memcpy(void *dst, void *src, uint64_t size)
{
	const uintptr_t	ptr_mask = sizeof(uint64_t) - 1;
	uint64_t		*lu_dst;
	uint64_t		*lu_src;
	uint32_t		i;

	if (!src)
		return (src);
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

void	ft_strlcpy(char *dst, char *src, uint64_t dst_size)
{
	uint64_t	f_size;

	if (!dst_size)
		return ;
	f_size = ft_strlen(src);
	if (f_size >= dst_size)
		f_size = dst_size - 1;
	ft_memcpy(dst, src, f_size);
	dst[f_size] = 0;
}

void	ft_strnlcpy(char *dst, char *src, uint64_t dst_size, uint64_t src_size)
{
	uint64_t	f_size;

	if (!dst_size)
		return ;
	f_size = ft_strlen(src);
	if (f_size > src_size)
		f_size = src_size;
	if (f_size >= dst_size)
		f_size = dst_size - 1;
	ft_memcpy(dst, src, f_size);
	dst[f_size] = 0;
}

// Return false if not the same
bool	ft_memcpm(void *s1, void *s2, uint64_t n)
{
	while (n--)
		if (((char *)s1)[n] != ((char *)s2)[n])
			return (false);
	return (true);
}

uint64_t	char_chr(const char str[], const char find)
{
	uint64_t	i;

	i = 0;
	while (str[i] && str[i] != find)
		++i;
	return (i);
}

char	*ft_strchr(char str[], const char to_find)
{
	uint64_t	i;

	i = 0;
	while (str[i] && str[i] != to_find)
		++i;
	if (str[i] == to_find)
		return (str + i);
	return (0);
}
