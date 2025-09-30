/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:29:01 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/30 13:19:42 by gaeudes          ###   ########.fr       */
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

__attribute__ ((pure, nonnull, flatten))
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

void	*ft_calloc(const uint64_t	size)
{
	void	*new;

	new = malloc(size);
	if (!new)
		return (NULL);
	return (ft_bzero(new, size));
}
