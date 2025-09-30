/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_strchr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:14:12 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/30 13:17:16 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

__attribute__((nonnull, pure))
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
char	*ft_sn_strchr(const char str[], const uint64_t lenstr,
	const char tofind[])
{
	uint32_t	i;

	i = 0;
	while (i < lenstr)
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
char	*ft_sn_strrchr(const char str[], const uint64_t lenstr,
	const char tofind[])
{
	uint32_t	i;

	i = lenstr;
	while (i-- > 0)
	{
		if (ft_strchr(tofind, str[i]))
			return ((char *)&(str[i]));
	}
	return (NULL);
}

__attribute__((nonnull, pure))
uint64_t	index_strchr(const char str[], const char find)
{
	uint64_t	i;

	i = 0;
	while (str[i] && str[i] != find)
		++i;
	return (i);
}
