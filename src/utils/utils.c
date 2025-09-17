/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:29:01 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/17 12:10:26 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

__attribute__ ((pure, nonnull, hot))
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

__attribute__ ((pure, nonnull, hot))
uint64_t	heap_strlen(const char str[])
{
	const char	*start = str;

	while (*str)
		++str;
	return (str - start);
}

__attribute__ ((pure, nonnull))
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

__attribute__((nonnull(1), hot))
void	*ft_clrset(t_clr *img_data, const t_clr color, const uint64_t size)
{
	uint64_t	i;

	i = 0;
	while (i < size)
	{
		img_data[i] = color;
		++i;
	}
	return (img_data);
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

// Return false if not the same
bool	ft_memcpm(void *s1, void *s2, uint64_t n)
{
	while (n--)
		if (((char *)s1)[n] != ((char *)s2)[n])
			return (false);
	return (true);
}

uint64_t	index_strchr(const char str[], const char find)
{
	uint64_t	i;

	i = 0;
	while (str[i] && str[i] != find)
		++i;
	return (i);
}

__attribute__((nonnull, pure, flatten))
char	*ft_strchr(const char str[], const char to_find)
{
	uint64_t	i;

	i = 0;
	while (str[i] && str[i] != to_find)
		++i;
	if (str[i] == to_find)
		return ((char *)str + i);
	return (0);
}

__attribute__((nonnull, pure, flatten))
char	*ft_s_strchr(const char str[], const char tofind[])
{
	uint32_t	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(tofind, str[i]))
			return ((char *)&(str[i]));
		++i;
	}
	return (NULL);
}

__attribute__((nonnull, pure, flatten))
char	*ft_strrchr(const char str[], const char to_find)
{
	uint64_t	i;

	i = heap_strlen(str);
	while (i-- > 0)
	{
		if (str[i] == to_find)
			return ((char *)&str[i]);
	}
	return (NULL);
}

__attribute__((nonnull, pure, flatten))
char *ft_s_strrchr(const char str[], const char tofind[])
{
	uint32_t	i;

	i = heap_strlen(str);
	while (i-- > 0)
	{
		if (ft_strchr(tofind, str[i]))
			return ((char *)&(str[i]));
	}
	return (NULL);
}

void	*ft_calloc(const uint64_t	size)
{
	void	*new;

	new = malloc(size);
	if (!new)
		return (NULL);
	return (ft_bzero(new, size));
}

void	ft_lutoacpy(const uint64_t nb, char str[], const uint64_t size)
{
	uint64_t	i;
	uint64_t	pow;

	pow = 10;
	i = 0;
	while (nb / pow) // who tf is gonna overflow that
		pow *= 10;
	while (pow / 10 && i < size - 1)
	{
		pow /= 10;
		str[i] = nb / pow % 10 + '0';
		++i;
	}
	str[i] = '\0';
}
