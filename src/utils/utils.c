/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:29:01 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/28 12:44:56 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "debug.h"
uint64_t	ft_strlen(char str[])
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

bool	ft_strendcmp(char str[], char end[])
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

void		*ft_memcpy(void *dst, void *src, uint64_t size)
{
	const uintptr_t	ptr_mask = sizeof(uint64_t) - 1;
	uint64_t		*lu_dst;
	uint64_t		*lu_src;
	uint32_t		i;

	while (size && ((uintptr_t)src & ptr_mask))
	{
		--size;
		*(uint8_t *)(dst++) = *(uint8_t *)(src++);
	}
	lu_dst = dst;
	lu_src = src;
	src += size &~ptr_mask;
	dst += size &~ptr_mask;
	i = size >> 3;
	while (i--)
		lu_dst[i] = lu_src[i];
	size &= ptr_mask;
	while (size--)
		*(uint8_t *)(dst++) = *(uint8_t *)(src++);
	return (dst - size);
}
